/** \file
    \brief Implementation of the muParserX engine.

<pre>
               __________                                 ____  ___
    _____  __ _\______   \_____ _______  ______ __________\   \/  /
   /     \|  |  \     ___/\__  \\_  __ \/  ___// __ \_  __ \     / 
  |  Y Y  \  |  /    |     / __ \|  | \/\___ \\  ___/|  | \/     \ 
  |__|_|  /____/|____|    (____  /__|  /____  >\___  >__| /___/\  \
        \/                     \/           \/     \/           \_/
                                       Copyright (C) 2012 Ingo Berg
                                       All rights reserved.

  muParserX - A C++ math parser library with array and string support
  Copyright (c) 2012, Ingo Berg
  All rights reserved.

  Redistribution and use in source and binary forms, with or without 
  modification, are permitted provided that the following conditions are met:

   * Redistributions of source code must retain the above copyright notice, 
     this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright notice, 
     this list of conditions and the following disclaimer in the documentation 
     and/or other materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
  POSSIBILITY OF SUCH DAMAGE.
</pre>
*/
#include "mpParserBase.h"

#include <cassert>
#include <cmath>
#include <memory>
#include <vector>
#include <sstream>

#include "utGeneric.h"
#include "mpDefines.h"
#include "mpIfThenElse.h"
#include "mpScriptTokens.h"

using namespace std;


MUP_NAMESPACE_START

  //------------------------------------------------------------------------------
  const char_type *g_sCmdCode[] = { _T("BRCK. OPEN     "),
                                    _T("BRCK. CLOSE    "),
                                    _T("IDX OPEN       "),
                                    _T("IDX CLOSE      "),
                                    _T("ARG_SEP        "),
                                    _T("IF             "),
                                    _T("ELSE           "),
                                    _T("ENDIF          "),
                                    _T("JMP            "),
                                    _T("VAR            "),
                                    _T("VAL            "),
                                    _T("FUNC           "),
                                    _T("OPRT_BIN       "),
                                    _T("OPRT_IFX       "),
                                    _T("OPRT_PFX       "),
                                    _T("END            "),
                                    _T("SCRIPT_GOTO    "),
                                    _T("SCRIPT_LABEL   "),
                                    _T("SCRIPT_FOR     "),
                                    _T("SCRIPT_IF      "),
                                    _T("SCRIPT_ELSE    "),
                                    _T("SCRIPT_ELSEIF  "),
                                    _T("SCRIPT_ENDIF   "),
                                    _T("SCRIPT_NEWLINE "),
                                    _T("SCRIPT_FUNCTION"),
                                    _T("UNKNOWN        ") };

  //------------------------------------------------------------------------------
  bool ParserXBase::s_bDumpStack = false;
  bool ParserXBase::s_bDumpRPN = false;

  //------------------------------------------------------------------------------
  /** \brief Identifiers for built in binary operators. 

      When defining custom binary operators with AddOprt(...) make sure not to choose 
      names conflicting with these definitions. 
  */
  const char_type* ParserXBase::c_DefaultOprt[] = { _T("("), 
                                                    _T(")"), 
                                                    _T("["), 
                                                    _T("]"), 
                                                    _T(","),
                                                    _T("?"),
                                                    _T(":"),
                                                    0 };

  //------------------------------------------------------------------------------
  /** \brief Default constructor. */
  ParserXBase::ParserXBase()
    :m_FunDef()
    ,m_PostOprtDef()
    ,m_InfixOprtDef()
    ,m_OprtDef()
    ,m_valConst()
    ,m_VarDef()
	,m_pParserEngine(&ParserXBase::ParseFromString)
    ,m_pTokenReader()
    ,m_valDynVarShadow()
    ,m_sNameChars()
    ,m_sOprtChars()
    ,m_sInfixOprtChars()
    ,m_nFinalResultIdx(0)
    ,m_bIsQueryingExprVar(false)
    ,m_bAutoCreateVar(false)
    ,m_rpn()
    ,m_vStackBuffer()
  {
    InitTokenReader();
  }

  //---------------------------------------------------------------------------
  /** \brief Copy constructor.
      \param a_Parser Reference to the other parser object

    Implemented by calling Assign(a_Parser)
  */
  ParserXBase::ParserXBase(const ParserXBase &a_Parser)
    :m_FunDef()
    ,m_PostOprtDef()
    ,m_InfixOprtDef()
    ,m_OprtDef()
    ,m_valConst()
    ,m_VarDef()
	,m_pParserEngine(&ParserXBase::ParseFromString)
    ,m_pTokenReader()
    ,m_valDynVarShadow()
    ,m_sNameChars()
    ,m_sOprtChars()
    ,m_sInfixOprtChars()
    ,m_nFinalResultIdx(0)
    ,m_bAutoCreateVar()
    ,m_rpn()
    ,m_vStackBuffer()
  {
    m_pTokenReader.reset(new TokenReader(this));
    Assign(a_Parser);
  }

  //---------------------------------------------------------------------------
  /** \brief Destructor.
      \throw nothrow
  */
  ParserXBase::~ParserXBase()
  {
    // It is important to release the stack buffer before
    // releasing the value cache. Since it may contain
    // Values referencing the cache.
    m_vStackBuffer.clear();
    m_cache.ReleaseAll();
  }

  //---------------------------------------------------------------------------
  /** \brief Assignement operator. 
      \param a_Parser Object to copy to this.
      \return *this
      \throw nothrow
      
    Implemented by calling Assign(a_Parser). Self assignement is suppressed.
  */
  ParserXBase& ParserXBase::operator=(const ParserXBase &a_Parser)
  {
    Assign(a_Parser);
    return *this;
  }

  //---------------------------------------------------------------------------
  /** \brief Copy state of a parser object to this. 
      \param a_Parser the source object.

    Clears Variables and Functions of this parser.
    Copies the states of all internal variables.
    Resets parse function to string parse mode.
  */
  void ParserXBase::Assign(const ParserXBase &ref)
  {
    if (&ref==this)
      return;

    // Don't copy bytecode instead cause the parser to create new bytecode 
    // by resetting the parse function.
    ReInit();

    m_pTokenReader.reset(ref.m_pTokenReader->Clone(this));

    m_OprtDef         = ref.m_OprtDef;
    m_FunDef          = ref.m_FunDef;
    m_PostOprtDef     = ref.m_PostOprtDef;
    m_InfixOprtDef    = ref.m_InfixOprtDef;
    m_valConst        = ref.m_valConst;
    m_valDynVarShadow = ref.m_valDynVarShadow;
    m_VarDef          = ref.m_VarDef;             // Copy user defined variables
    m_nFinalResultIdx = ref.m_nFinalResultIdx;

    // Copy charsets
    m_sNameChars = ref.m_sNameChars;
    m_sOprtChars = ref.m_sOprtChars;
    m_sInfixOprtChars = ref.m_sInfixOprtChars;

    m_bAutoCreateVar = ref.m_bAutoCreateVar;

    // Things that should not be copied:
    // - m_vStackBuffer
    // - m_cache
    // - m_rpn
  }

  //---------------------------------------------------------------------------
  /** \brief Evaluate the expression.
      \pre A formula must be set.
      \pre Variables must have been set (if needed)
      \sa SetExpr
      \return The evaluation result
      \throw ParseException if no Formula is set or in case of any other error related to the formula.

      A note on const correctness: 
      I consider it important that Calc is a const function.
      Due to caching operations Calc changes only the state of internal variables with one exception
      m_UsedVar this is reset during string parsing and accessible from the outside. Instead of making
      Calc non const GetExprVar is non const because it explicitely calls Eval() forcing this update. 
  */
  const IValue& ParserXBase::Eval() const
  {
    return (this->*m_pParserEngine)(); 
  }
  
  //---------------------------------------------------------------------------
  /** \brief Return the strings of all Operator identifiers. 
      \return Returns a pointer to the c_DefaultOprt array of const char *.
      \throw nothrow

      GetOprt is a const function returning a pinter to an array of const char pointers.
  */
  const char_type** ParserXBase::GetOprtDef() const
  {
    return (const char_type **)(&c_DefaultOprt[0]);
  }

  //---------------------------------------------------------------------------
  /** \brief Define the set of valid characters to be used in names of
              functions, variables, constants.
  */
  void ParserXBase::DefineNameChars(const char_type *a_szCharset)
  {
    m_sNameChars = a_szCharset;
  }

  //---------------------------------------------------------------------------
  /** \brief Define the set of valid characters to be used in names of
             binary operators and postfix operators.
      \param a_szCharset A string containing all characters that can be used 
                         in operator identifiers.
  */
  void ParserXBase::DefineOprtChars(const char_type *a_szCharset)
  {
    m_sOprtChars = a_szCharset;
  }

  //---------------------------------------------------------------------------
  /** \brief Define the set of valid characters to be used in names of
             infix operators.
      \param a_szCharset A string containing all characters that can be used 
                         in infix operator identifiers.
  */
  void ParserXBase::DefineInfixOprtChars(const char_type *a_szCharset)
  {
    m_sInfixOprtChars = a_szCharset;
  }

  //---------------------------------------------------------------------------
  /** \brief Virtual function that defines the characters allowed in name identifiers. 
      \sa #ValidOprtChars, #ValidPrefixOprtChars
  */ 
  const char_type* ParserXBase::ValidNameChars() const
  {
    assert(m_sNameChars.size());
    return m_sNameChars.c_str();
  }

  //---------------------------------------------------------------------------
  /** \brief Virtual function that defines the characters allowed in operator definitions. 
      \sa #ValidNameChars, #ValidPrefixOprtChars
  */
  const char_type* ParserXBase::ValidOprtChars() const
  {
    assert(m_sOprtChars.size());
    return m_sOprtChars.c_str();
  }

  //---------------------------------------------------------------------------
  /** \brief Virtual function that defines the characters allowed in infix operator definitions.
      \sa #ValidNameChars, #ValidOprtChars
  */
  const char_type* ParserXBase::ValidInfixOprtChars() const
  {
    assert(m_sInfixOprtChars.size());
    return m_sInfixOprtChars.c_str();
  }


  //---------------------------------------------------------------------------
  /** \brief Initialize the token reader. 
      \post m_pTokenReader.Get()!=0
      \throw nothrow

    Create new token reader object and submit pointers to function, operator,
    constant and variable definitions.
  */
  void ParserXBase::InitTokenReader()
  {
    m_pTokenReader.reset(new TokenReader(this));
  }

  //---------------------------------------------------------------------------
  /** \brief Reset parser to string parsing mode and clear internal buffers.
      \throw nothrow

      Resets the token reader.
  */
  void ParserXBase::ReInit() const
  {
    m_pParserEngine = &ParserXBase::ParseFromString;
    m_pTokenReader->ReInit();
    m_rpn.Reset();
    m_vStackBuffer.clear();
  }

  //---------------------------------------------------------------------------
  /** \brief Adds a new package to the parser. 
  
    The parser becomes the owner of the package pointer and is responsible for 
    its deletion.
  */
  void ParserXBase::AddPackage(IPackage *p)
  {
    p->AddToParser(this);
  }

  //---------------------------------------------------------------------------
  void ParserXBase::RemovePackage(IPackage * /*p*/)
  {
  }

  //---------------------------------------------------------------------------
  /** \brief Add a value reader object to muParserX. 
      \param a_pReader Pointer to the value reader object.
  */
  void ParserXBase::AddValueReader(IValueReader *a_pReader)
  {
    m_pTokenReader->AddValueReader(a_pReader);
  }

  //---------------------------------------------------------------------------
  /** \brief Check if a given name contains invalid characters. 
      \param a_strName The name to check
      \param a_szCharSet The characterset
      \throw ParserException if the name contains invalid charakters.
  */
  void ParserXBase::CheckName(const string_type &a_strName, 
                              const string_type &a_szCharSet) const
  {
    if ( !a_strName.length() || 
        (a_strName.find_first_not_of(a_szCharSet)!=string_type::npos) ||
        (a_strName[0]>=(char_type)'0' && a_strName[0]<=(char_type)'9'))
    {
      Error(ecINVALID_NAME);
    }
  }

  //---------------------------------------------------------------------------
  /** \brief Set the mathematical expression. 
      \param a_sExpr String with the expression
      \throw ParserException in case of syntax errors.

      Triggers first time calculation thus the creation of the bytecode and 
      scanning of used variables.
  */
  void ParserXBase::SetExpr(const string_type &a_sExpr)
  {
    m_pTokenReader->SetExpr(a_sExpr);
    ReInit();
  }

  //---------------------------------------------------------------------------
  /** \brief Add a user defined operator. 
      \post Will reset the Parser to string parsing mode.
      \param a_pOprt Pointer to a unary postfix operator object. The parser will
                     become the new owner of this object hence will destroy it.
  */
  void ParserXBase::DefinePostfixOprt(IOprtPostfix *a_pOprt)
  {
    m_PostOprtDef[a_pOprt->GetIdent()] = ptr_tok_type(a_pOprt);
    ReInit();
  }

  //---------------------------------------------------------------------------
  /** \brief Add a user defined operator. 
      \param a_pOprt Pointer to a unary postfix operator object. The parser will
             become the new owner of this object hence will destroy it.
  */
  void ParserXBase::DefineInfixOprt(IOprtInfix *a_pOprt)
  {
    m_InfixOprtDef[a_pOprt->GetIdent()] = ptr_tok_type(a_pOprt);
    ReInit();
  }

  //---------------------------------------------------------------------------
  /** \brief Add a user defined variable. 
      \param a_sName The variable name
      \param a_Var The variable to be added to muParserX
  */
  void ParserXBase::DefineVar(const string_type &a_sName, const Variable &a_Var)
  {
    CheckName(a_sName, ValidNameChars());
    m_VarDef[a_sName] = ptr_tok_type( a_Var.Clone() );
    ReInit();
  }
  

  //---------------------------------------------------------------------------
  /** \brief Define a parser Constant. 
      \param a_sName The name of the constant
      \param a_Val Const reference to the constants value

    Parser constants are handed over by const reference as opposed to variables 
    which are handed over by reference. Consequently the parser can not change 
    their value.
  */
  void ParserXBase::DefineConst(const string_type &a_sName, const Value &a_Val)
  {
    CheckName(a_sName, ValidNameChars());
    m_valConst[a_sName] = ptr_tok_type( a_Val.Clone() );
    ReInit();
  }

  //---------------------------------------------------------------------------
  /** \brief Add a callback object to the parser. 
      \param a_pFunc Pointer to the intance of a parser callback object 
                     representing the function.
      \sa GetFunDef, functions

    The parser takes ownership over the callback object.
  */
  void ParserXBase::DefineFun(ICallback *a_pFunc)
  {
    a_pFunc->SetParent(this);
    m_FunDef[ a_pFunc->GetIdent() ] = ptr_tok_type(a_pFunc);
  }

  //---------------------------------------------------------------------------
  /** \brief Define a binara operator. 
      \param a_pCallback Pointer to the callback object
  */
  void ParserXBase::DefineOprt(IOprtBin *a_pCallback)
  {
    a_pCallback->SetParent(this);
    m_OprtDef.insert(make_pair(a_pCallback->GetIdent(), ptr_tok_type(a_pCallback)));
  }

  //---------------------------------------------------------------------------
  /** \brief Return a map containing the used variables only. */
  const var_maptype& ParserXBase::GetExprVar() const
  {
    utils::scoped_setter<bool> guard2(m_bIsQueryingExprVar, true);

    // Create RPN,  but do not compute the result or switch to RPN
    // parsing mode. The expression may contain yet to be defined variables.
    CreateRPN();
    return m_pTokenReader->GetUsedVar();
  }

  //---------------------------------------------------------------------------
  /** \brief Return a map containing the used variables only. */
  const var_maptype& ParserXBase::GetVar() const
  {
    return m_VarDef;
  }

  //---------------------------------------------------------------------------
  /** \brief Return a map containing all parser constants. */
  const val_maptype& ParserXBase::GetConst() const
  {
    return m_valConst;
  }

  //---------------------------------------------------------------------------
  /** \brief Return prototypes of all parser functions.
      \return #m_FunDef
      \sa FunProt, functions
      \throw nothrow

    The return type is a map of the public type #funmap_type containing the prototype
    definitions for all numerical parser functions. String functions are not part of 
    this map. The Prototype definition is encapsulated in objects of the class FunProt
    one per parser function each associated with function names via a map construct.
  */
  const fun_maptype& ParserXBase::GetFunDef() const
  {
    return m_FunDef;
  }

  //---------------------------------------------------------------------------
  /** \brief Retrieve the mathematical expression. */
  const string_type& ParserXBase::GetExpr() const
  {
    return m_pTokenReader->GetExpr();
  }

  //---------------------------------------------------------------------------
  /** \brief Get the version number of muParserX. 
      \return A string containing the version number of muParserX.
  */
  string_type ParserXBase::GetVersion() 
  {
    return MUP_PARSER_VERSION;
  }

  //---------------------------------------------------------------------------
  void ParserXBase::ApplyRemainingOprt(Stack<ptr_tok_type> &stOpt,
                                           Stack<ptr_val_type> &stVal) const


  {
    while (stOpt.size() &&
           stOpt.top()->GetCode() != cmBO && 
           stOpt.top()->GetCode() != cmIO && 
           stOpt.top()->GetCode() != cmIF)
    {
      ptr_tok_type &op = stOpt.top();
                      
      switch(op->GetCode())
      {
        case  cmOPRT_BIN:
              MUP_ASSERT(stOpt.top()->GetCode()==cmOPRT_BIN);
              ApplyFunc(stOpt, stVal, 2);
              break;

        case  cmELSE:
              ApplyIfElse(stOpt, stVal);
              break;

        default:
              Error(ecINTERNAL_ERROR);
      } // switch operator token type
    } // While operator stack not empty
  }

  //---------------------------------------------------------------------------
  /** \brief Calls a parser function with its corresponding arguments. 
      \param a_stOpt The operator stack
      \param a_stVal The value stack
      \param a_iArgCount The number of function arguments
  */
  void ParserXBase::ApplyFunc(Stack<ptr_tok_type> &a_stOpt,
                              Stack<ptr_val_type> &a_stVal, 
                              int a_iArgCount) const
  { 
    if (a_stOpt.empty())
      return;

    ptr_tok_type tok = a_stOpt.pop();
    ICallback *pFun = tok->AsICallback();

    int iArgCount = (pFun->GetArgc()>=0) ? pFun->GetArgc() : a_iArgCount;
    int iOffset = a_stVal.size() - iArgCount;
    MUP_VERIFY(iOffset>=0);

    // The paramater stack may be empty since functions may not
    // have a parameter. They do always have a return value though.
    // If the param stack is empty create an entry for the function 
    // return value.
    if (iArgCount==0)
      a_stVal.push(ptr_val_type(new Value()));

    MUP_VERIFY((std::size_t)iOffset<a_stVal.size());
    ptr_val_type *pArg = a_stVal.get_data() + iOffset;
    
    //if (pFun->GetArgc()==0)
    //  a_stVal.push(ptr_val_type(new Value()));

    //ptr_val_type *pArg = a_stVal.get_data() + iOffset;

    try
    {
      // Make sure to pass on a volatile flag to the function result
      bool bResultIsVolatile = false;
      for (int i=0; i<iArgCount && bResultIsVolatile==false; ++i)
      {
        if (pArg[i]->IsFlagSet(IToken::flVOLATILE))
          bResultIsVolatile = true;
      }

      // Instead of evaluating the function merely a dummy value of the same type as the function return value
      // is created 
      *pArg = ptr_val_type(new Value());
      pFun->SetNumArgsPresent(iArgCount);
      
      if (bResultIsVolatile)
        (*pArg)->AddFlags(IToken::flVOLATILE);

      m_rpn.Add(tok);
    }
    catch(ParserError &e)
    {
      // This are type related errors caused by undefined
      // variables. They must be ignored if the parser is
      // just checking the presence of expression variables
      if (!m_bIsQueryingExprVar)
      {
        ErrorContext &err = e.GetContext();
        err.Pos   = m_pTokenReader->GetPos();
        err.Expr  = m_pTokenReader->GetExpr();

        if (err.Ident.empty())
          err.Ident = pFun->GetIdent();

        throw;
      }
    }

    if (iArgCount>0)
      a_stVal.pop(iArgCount-1); // remove the arguments
  }

  //---------------------------------------------------------------------------
  void ParserXBase::ApplyIfElse(Stack<ptr_tok_type> &a_stOpt,
                                Stack<ptr_val_type> &a_stVal) const
  { 
    while (a_stOpt.size() && a_stOpt.top()->GetCode()==cmELSE)
    {
      MUP_ASSERT(a_stOpt.size()>0);
      MUP_ASSERT(a_stVal.size()>=3);
      MUP_ASSERT(a_stOpt.top()->GetCode()==cmELSE);

      // it then else is a ternary operator Pop all three values from the value 
      // stack and just return the right value
      ptr_val_type vVal2 = a_stVal.pop();
      ptr_val_type vVal1 = a_stVal.pop();
      ptr_val_type bExpr = a_stVal.pop();

      // Push a dummy value of the correct type
      a_stVal.push(ptr_val_type(new Value(/*cType*/)));
      
      // Pass on volatile flags
      if (vVal1->IsFlagSet(IToken::flVOLATILE) || vVal2->IsFlagSet(IToken::flVOLATILE))
        a_stVal.top()->AddFlags(IToken::flVOLATILE);

      ptr_tok_type opElse = a_stOpt.pop();
      ptr_tok_type opIf = a_stOpt.pop();
      MUP_ASSERT(opElse->GetCode()==cmELSE)
      MUP_ASSERT(opIf->GetCode()==cmIF)
      
      m_rpn.Add(ptr_tok_type(new TokenIfThenElse(cmENDIF)));
    }
  }

  //---------------------------------------------------------------------------
  void ParserXBase::DumpRPN() const
  {
    m_rpn.AsciiDump();
  }

  //---------------------------------------------------------------------------
  void ParserXBase::CreateRPN() const
  {
    if (!m_pTokenReader->GetExpr().length()) 
      Error(ecUNEXPECTED_EOF, 0);

    // The Stacks take the ownership over the tokens
    Stack<ptr_tok_type> stOpt;
    Stack<ptr_val_type> stVal;
    Stack<ICallback*>   stFunc;  
    Stack<int>  stArgCount;
    Stack<int>  stIdxCount;
    ptr_tok_type pTok, pTokPrev;
    Value val;    

    ReInit();

    // The outermost counter counts the number of seperated items
    // such as in "a=10,b=20,c=c+a"
    stArgCount.push(1);

    for(bool bLoop=true; bLoop;)
    {
      pTokPrev = pTok;
      pTok = m_pTokenReader->ReadNextToken();

#if defined(MUP_DUMP_TOKENS)
      cout << pTok->AsciiDump() << endl;
#endif
      ECmdCode eCmd = pTok->GetCode();
      switch (eCmd)
      {
      case  cmVAR:
      case  cmVAL:
            {
              IValue *pVal = pTok->AsIValue();
              if (stFunc.empty() && pVal->GetType()=='n')
              {
                ErrorContext err;
                err.Errc  = ecUNEXPECTED_PARENS;
                err.Ident = _T(")");
                err.Pos   = pTok->GetExprPos();
                throw ParserError(err);
              }

              stVal.push( ptr_val_type(pVal) );
              
              // Arrays can't be added directly to the reverse polish notation
              // since there may be an index operator following next...
              m_rpn.Add(pTok);

              // Apply infix operator if existant
              if (stOpt.size() && stOpt.top()->GetCode()==cmOPRT_INFIX) 
                ApplyFunc(stOpt, stVal, 1);
            }
            break;

      case  cmIC:
            {
              // The argument count for parameterless functions is zero
              // by default an opening bracket sets parameter count to 1
              // in preparation of arguments to come. If the last token
              // was an opening bracket we know better...
              if (pTokPrev.Get()!=NULL && pTokPrev->GetCode()==cmIO)
                --stArgCount.top();

              ApplyRemainingOprt(stOpt, stVal);

              // if opt is "]" and opta is "[" the bracket content has been evaluated.
              // Now its time to check if there is either a function or a sign pending.
              // - Neither the opening nor the closing bracket will be pushed back to
              //   the operator stack
              // - Check if a function is standing in front of the opening bracket, 
              //   if so evaluate it afterwards to apply an infix operator.
              if ( stOpt.size() && stOpt.top()->GetCode()==cmIO )
              {
                //
                // Find out how many dimensions were used in the index operator.
                //
                std::size_t iArgc = stArgCount.pop();

                stOpt.pop(); // Take opening bracket from stack
                
                IOprtIndex *pOprtIndex = pTok->AsIOprtIndex();
                MUP_ASSERT(pOprtIndex!=NULL);

                pOprtIndex->SetNumArgsPresent(iArgc);
                m_rpn.Add(pTok);
                
                // Pop the index values from the stack
                MUP_ASSERT(stVal.size()>=iArgc+1); 
                for (std::size_t i=0; i<iArgc; ++i)
                  stVal.pop();

                // Now i would need to pop the topmost value from the stack, apply the index
                // opertor and push the result back to the stack. But here we are just creating the
                // RPN and are working with dummy values anyway so i just mark the topmost value as 
                // volatile and leave it were it is. The real index logic is in the RPN evaluator...
                stVal.top()->AddFlags(IToken::flVOLATILE);
              } // if opening index bracket is on top of operator stack
            }
            break;

      case  cmBC:
            {
              // The argument count for parameterless functions is zero
              // by default an opening bracket sets parameter count to 1
              // in preparation of arguments to come. If the last token
              // was an opening bracket we know better...
              if (pTokPrev.Get()!=NULL && pTokPrev->GetCode()==cmBO)
                --stArgCount.top();

              ApplyRemainingOprt(stOpt, stVal);

              // if opt is ")" and opta is "(" the bracket content has been evaluated.
              // Now its time to check if there is either a function or a sign pending.
              // - Neither the opening nor the closing bracket will be pushed back to
              //   the operator stack
              // - Check if a function is standing in front of the opening bracket, 
              //   if so evaluate it afterwards to apply an infix operator.
              if ( stOpt.size() && stOpt.top()->GetCode()==cmBO )
              {
                //
                // Here is the stuff to evaluate a function token
                //
                int iArgc = stArgCount.pop();

                stOpt.pop(); // Take opening bracket from stack
                if ( stOpt.empty() )
                  break;
                  
                if ( (stOpt.top()->GetCode()!=cmFUNC) && (stOpt.top()->GetCode()!=cmOPRT_INFIX) )
                  break;

                ICallback *pFun = stOpt.top()->AsICallback();
                stFunc.pop(); 

                if (pFun->GetArgc()!=-1 && iArgc > pFun->GetArgc())
                  Error(ecTOO_MANY_PARAMS, pTok->GetExprPos(), pFun);

                if (iArgc < pFun->GetArgc())
                  Error(ecTOO_FEW_PARAMS, pTok->GetExprPos(), pFun);

                // Evaluate the function
                ApplyFunc(stOpt, stVal, iArgc);

                // Apply an infix operator, if present
                if (stOpt.size() && stOpt.top()->GetCode()==cmOPRT_INFIX) 
                  ApplyFunc(stOpt, stVal, 1);
              }
            }
            break;

      case  cmELSE:
            ApplyRemainingOprt(stOpt, stVal);
            m_rpn.Add(pTok);
            stOpt.push(pTok);
            break;

      case  cmSCRIPT_NEWLINE:
            {
              ApplyRemainingOprt(stOpt, stVal);

              // Value stack plätten
              // Stack der RPN um die Anzahl im stack enthaltener Werte zurück setzen
              int n = stVal.size();
              m_rpn.AddNewline(pTok, n);
              stVal.clear();
              stOpt.clear();
            }
            break;

      case  cmARG_SEP:
            if (stArgCount.empty())
              Error(ecUNEXPECTED_COMMA, m_pTokenReader->GetPos());

            ++stArgCount.top();

            //if (stVal.size()) // increase argument counter
            //  stArgCount.top()++;

            ApplyRemainingOprt(stOpt, stVal);
            break;

      case  cmEOE:
            ApplyRemainingOprt(stOpt, stVal);
            m_rpn.Finalize();
            break;

      case  cmIF:
      case  cmOPRT_BIN:
            {
              while ( stOpt.size() && 
                      stOpt.top()->GetCode() != cmBO && 
                      stOpt.top()->GetCode() != cmIO && 
                      stOpt.top()->GetCode() != cmELSE &&
                      stOpt.top()->GetCode() != cmIF)
              {
                IToken *pOprt1 = stOpt.top().Get();
                IToken *pOprt2 = pTok.Get();
                MUP_ASSERT(pOprt1 && pOprt2);  
                MUP_ASSERT(pOprt1->AsIPrecedence() && pOprt2->AsIPrecedence());  

                int nPrec1 = pOprt1->AsIPrecedence()->GetPri(),
                    nPrec2 = pOprt2->AsIPrecedence()->GetPri();

                if (pOprt1->GetCode()==pOprt2->GetCode())
                {
                  // Deal with operator associativity
                  EOprtAsct eOprtAsct = pOprt1->AsIPrecedence()->GetAssociativity();
                  if ( (eOprtAsct==oaRIGHT && (nPrec1 <= nPrec2)) || 
                       (eOprtAsct==oaLEFT  && (nPrec1 <  nPrec2)) )
                  {
                    break;
                  }
                }
                else if (nPrec1 < nPrec2)
                {
                  break;
                }
                
                // apply the operator now 
                // (binary operators are identic to functions with two arguments)
                ApplyFunc(stOpt, stVal, 2);
              } // while ( ... )

              if (pTok->GetCode()==cmIF)
                m_rpn.Add(pTok);

              stOpt.push(pTok);
            }
            break;

      //
      //  Postfix Operators
      //
      case  cmOPRT_POSTFIX:
            {
              MUP_ASSERT(stVal.size());

              ptr_val_type &pVal(stVal.top());
              try
              {
                // place a dummy return value into the value stack, do not
                // evaluate pOprt (this is important for lazy evaluation!)
                // The only place where evaluation takes place is the RPN 
                // engine!
                pVal = ptr_val_type(new Value());
                m_rpn.Add(pTok);
              }
              catch(ParserError &)
              {
                if (!m_bIsQueryingExprVar)
                  throw;
              }
            }
  		      break;

      case  cmIO:
      case  cmBO:    
            stOpt.push(pTok);
            stArgCount.push(1);
            break;

      //
      // Functions
      //
      case  cmOPRT_INFIX:
      case  cmFUNC:
            {
              ICallback *pFunc = pTok->AsICallback();
              MUP_ASSERT(pFunc);

              // Check if this function is a argument to another function
              // if so check if the the return type fits.
              if (!stFunc.empty() && stFunc.top()->GetCode()==cmFUNC)
              {
                MUP_ASSERT(stArgCount.size());
                int iArgc = (int)stArgCount.top() /*+ 1*/;

                ICallback *pOuterFunc = stFunc.top();
                if (pOuterFunc->GetArgc()!=-1 && iArgc>pOuterFunc->GetArgc())
		              Error(ecTOO_MANY_PARAMS, m_pTokenReader->GetPos());

                MUP_ASSERT(pOuterFunc->GetArgc()==-1 || iArgc<=pOuterFunc->GetArgc());
              }

              stOpt.push(pTok);  
              stFunc.push(pFunc); // to collect runtime type information
            }
	          break;

      default: 
            Error(ecINTERNAL_ERROR);
      } // switch Code

      if (ParserXBase::s_bDumpStack)
      {
        StackDump( stVal, stOpt );
      }

      if ( pTok->GetCode() == cmEOE )
        bLoop = false;
    } // for (all tokens)

    if (ParserXBase::s_bDumpRPN)
    {
      m_rpn.AsciiDump();
    }

    m_nFinalResultIdx = stArgCount.top()-1;
    MUP_ASSERT(stVal.size());
  }

  //---------------------------------------------------------------------------
  /** \brief One of the two main parse functions.
      \sa ParseCmdCode(), ParseValue()

    Parse expression from input string. Perform syntax checking and create bytecode.
    After parsing the string and creating the bytecode the function pointer 
    #m_pParseFormula will be changed to the second parse routine the uses bytecode instead of string parsing.
  */
  const IValue& ParserXBase::ParseFromString() const
  { 
    CreateRPN();

    // Umsachalten auf RPN
    m_vStackBuffer.assign(m_rpn.GetRequiredStackSize(), ptr_val_type());
    for (std::size_t i=0; i<m_vStackBuffer.size(); ++i)
    {
      Value *pValue = new Value;
      pValue->BindToCache(&m_cache);
      m_vStackBuffer[i].Reset(pValue);
    }

    m_pParserEngine = &ParserXBase::ParseFromRPN;

    return (this->*m_pParserEngine)();
  } 

  //---------------------------------------------------------------------------
  const IValue& ParserXBase::ParseFromRPN() const
  {
    ptr_val_type *pStack = &m_vStackBuffer[0];
    const ptr_tok_type *pRPN = &(m_rpn.GetData()[0]);

    int sidx = -1;
    std::size_t lenRPN = m_rpn.GetSize();
    for (std::size_t i=0; i<lenRPN; ++i)
    {
      IToken *pTok = pRPN[i].Get();
      ECmdCode eCode = pTok->GetCode();

      switch (eCode)
      {
      case cmSCRIPT_NEWLINE:
           sidx = -1; //-= static_cast<TokenNewline*>(pTok)->GetStackOffset();
           m_nFinalResultIdx = 0;
           continue;

      case cmVAR:
           {
             sidx++;
             assert(sidx<(int)m_vStackBuffer.size());
             pStack[sidx].Reset(static_cast<IValue*>(pTok));
           }
           continue;

      case cmVAL:
           {
             sidx++;
             assert(sidx<(int)m_vStackBuffer.size());
             ptr_val_type &val = pStack[sidx];
             if (val->GetCode()==cmVAR)
               val.Reset(m_cache.CreateFromCache());

             *val = *(static_cast<IValue*>(pTok));
           }
           continue;

      case  cmIC:
            {
              IOprtIndex *pIdxOprt = static_cast<IOprtIndex*>(pTok);
              int nArgs = pIdxOprt->GetArgsPresent();
              sidx -= nArgs - 1;
              assert(sidx>=0);

              ptr_val_type &idx = pStack[sidx];     // Pointer to the first index
              ptr_val_type &val = pStack[--sidx];   // Pointer to the variable or value beeing indexed
              pIdxOprt->At(val, &idx, nArgs);




/*

              // apply the index operator
              ptr_val_type &idx = pStack[sidx--];
              ptr_val_type &val = pStack[sidx];
              MUP_ASSERT(val->GetCode()==cmVAR);
             
              int i;
              try
              {
                i = idx->GetInteger();
                if (i<0)
                  Error(ecINDEX_OUT_OF_BOUNDS, pTok->GetExprPos(), val.Get());
              }
              catch(ParserError &exc)
              {
                if (exc.GetCode()==ecTYPE_CONFLICT)
                  Error(ecTYPE_CONFLICT_IDX, pTok->GetExprPos(), val.Get());
                else 
                  throw;
              }
              val.Reset(new Variable( &(val->At(i)) ) );
*/
            }
            continue;

      case cmOPRT_POSTFIX:
      case cmFUNC:
      case cmOPRT_BIN:
      case cmOPRT_INFIX:
           {
             ICallback *pFun = static_cast<ICallback*>(pTok);
             int nArgs = pFun->GetArgsPresent();
             sidx -= nArgs - 1;
             assert(sidx>=0);

             ptr_val_type &val = pStack[sidx];
             try
             {
               if (val->GetCode()==cmVAR)
               {
                 ptr_val_type buf(m_cache.CreateFromCache());
                 pFun->Eval(buf, &val, nArgs);
                 val = buf;
               }
               else
                 pFun->Eval(val, &val, nArgs);
             }
             catch(ParserError &exc)
             {
               ErrorContext err;
               err.Expr = m_pTokenReader->GetExpr();
               err.Ident = pFun->GetIdent();
               err.Errc = ecEVAL;
               err.Pos = pFun->GetExprPos();
               err.Hint = exc.GetMsg();
               throw ParserError(err);
             }
             catch(MatrixError & /*exc*/)
             {
               ErrorContext err;
               err.Expr = m_pTokenReader->GetExpr();
               err.Ident = pFun->GetIdent();
               err.Errc = ecEVAL;
               err.Pos = pFun->GetExprPos();
               err.Hint = _T("Matrix dimension mismatch");
               throw ParserError(err);
             }
           }
           continue;

      case cmIF:
           MUP_ASSERT(sidx>=0);
           if (pStack[sidx--]->GetBool()==false)
             i+=static_cast<TokenIfThenElse*>(pTok)->GetOffset();
           continue;

      case cmELSE:
      case cmJMP:
           i += static_cast<TokenIfThenElse*>(pTok)->GetOffset();
           continue;

      case cmENDIF:
           continue;

			default:
					Error(ecINTERNAL_ERROR);
      } // switch token
    } // for all RPN tokens

    return *pStack[m_nFinalResultIdx];
  }

  //---------------------------------------------------------------------------
  void  ParserXBase::Error(EErrorCodes a_iErrc, int a_iPos, const IToken *a_pTok) const
  {
    ErrorContext err;
    err.Errc = a_iErrc;
    err.Pos = a_iPos;
    err.Expr = m_pTokenReader->GetExpr();
    err.Ident = (a_pTok) ? a_pTok->GetIdent() : _T("");
    throw ParserError(err);
  }

  //------------------------------------------------------------------------------
  /** \brief Clear all user defined variables.
      \throw nothrow
      
      Resets the parser to string parsing mode by calling #ReInit.
  */
  void ParserXBase::ClearVar()
  {
    m_VarDef.clear();
    m_valDynVarShadow.clear();
    ReInit();
  }

  //------------------------------------------------------------------------------
  /** \brief Remove a variable from internal storage.
      \param a_strVarName Name of the variable to be removed.
      \throw nothrow

    Removes a variable if it exists. If the Variable does not exist 
    nothing will be done.
  */
  void ParserXBase::RemoveVar(const string_type &a_strVarName)
  {
    var_maptype::iterator item = m_VarDef.find(a_strVarName);
    if (item!=m_VarDef.end())
    {
      m_VarDef.erase(item);
      ReInit();
    }
  }

  //------------------------------------------------------------------------------
  /** \brief Clear the expression. 
      \throw nothrow

      Clear the expression and existing bytecode.
  */
  void ParserXBase::ClearExpr()
  {
    m_pTokenReader->SetExpr(_T(""));
    ReInit();
  }

  //------------------------------------------------------------------------------
  /** \brief Clear all function definitions. 
      \throw nothrow
  */
  void ParserXBase::ClearFun()
  {
    m_FunDef.clear();
    ReInit();
  }

  //------------------------------------------------------------------------------
  /** \brief Clear all user defined constants.
      \throw nothrow

      Both numeric and string constants will be removed from the internal storage.
  */
  void ParserXBase::ClearConst()
  {
    m_valConst.clear();
    ReInit();
  }

  //------------------------------------------------------------------------------
  /** \brief Clear all user defined postfix operators.
      \throw nothrow
  */
  void ParserXBase::ClearPostfixOprt()
  {
    m_PostOprtDef.clear();
    ReInit();
  }

  //------------------------------------------------------------------------------
  /** \brief Clear all user defined binary operators. 
      \throw nothrow
  */
  void ParserXBase::ClearOprt()
  {
    m_OprtDef.clear();
    ReInit();
  }

  //------------------------------------------------------------------------------
  /** \brief Clear the user defined Prefix operators. 
      \throw nothrow
  */
  void ParserXBase::ClearInfixOprt()
  {
    m_InfixOprtDef.clear();
    ReInit();
  }

  //------------------------------------------------------------------------------
  void ParserXBase::EnableAutoCreateVar(bool bStat)
  {
    m_bAutoCreateVar = bStat;
  }

  //------------------------------------------------------------------------------
  void ParserXBase::EnableOptimizer(bool bStat)
  {
    m_rpn.EnableOptimizer(bStat);
  }

  //---------------------------------------------------------------------------
  /** \brief Enable the dumping of bytecode amd stack content on the console. 
      \param bDumpCmd Flag to enable dumping of the current bytecode to the console.
      \param bDumpStack Flag to enable dumping of the stack content is written to the console.

     This function is for debug purposes only!
  */
  void ParserXBase::EnableDebugDump(bool bDumpRPN, bool bDumpStack)
  {
    ParserXBase::s_bDumpRPN   = bDumpRPN;
    ParserXBase::s_bDumpStack = bDumpStack;
  }

  //------------------------------------------------------------------------------
  bool ParserXBase::IsAutoCreateVarEnabled() const
  {
    return m_bAutoCreateVar;
  }

  //------------------------------------------------------------------------------
  /** \brief Dump stack content. 

      This function is used for debugging only.
  */
  void ParserXBase::StackDump(const Stack<ptr_val_type> &a_stVal, 
			             			      const Stack<ptr_tok_type> &a_stOprt) const
  {
    using std::cout;
    Stack<ptr_tok_type>  stOprt(a_stOprt); 
    Stack<ptr_val_type>  stVal(a_stVal);

    string_type sInfo = _T("StackDump>  ");
    console() << _T("\n") << sInfo << _T("Value stack:\n");
    console() << sInfo;
    while ( !stVal.empty() ) 
    {
      ptr_val_type val = stVal.pop();
      console() << _T("  ") << *(val.Get()) << _T(" ") << ((val->AsValue()!=NULL) ? _T("(Val)") : _T("(Var)"));
    }

    if (stOprt.empty())
      console() << _T("\n") << sInfo << _T("Operator stack is empty.\n");
    else
      console() << _T("\n") << sInfo << _T("Operator stack:\n");

    while ( !stOprt.empty() )
    {
      ptr_tok_type tok = stOprt.pop();
      console() << sInfo << _T(" ") << g_sCmdCode[tok->GetCode()] << _T(" \"") << tok->GetIdent() << _T("\" \n");
    }

    console() <<endl;
  }

} // namespace mu
