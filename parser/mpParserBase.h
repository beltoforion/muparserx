#ifndef MUP_PARSERBASE_H
#define MUP_PARSERBASE_H

/** \file
    \brief Definition of the muParserX engine.

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

#include <cmath>
#include <string>
#include <iostream>
#include <map>
#include <memory>

#include "mpIOprt.h"
#include "mpIValReader.h"
#include "mpIPackage.h"
#include "mpStack.h"
#include "mpTokenReader.h"
#include "mpError.h"
#include "mpValue.h"
#include "mpVariable.h"
#include "mpTypes.h"
#include "mpRPN.h"
#include "mpValueCache.h"

MUP_NAMESPACE_START
  
  /** \brief Implementation of the parser engine.
      \author Ingo Berg

    This is the muParser core. It provides the parsing logic and manages
    the callback functions, operators, variables and constants. Do not 
    instantiate this class directly. Create an instance of mup::ParserX instead.
  */
  class ParserXBase
  {
  friend class TokenReader;

  private:

    //typedef Value (ParserXBase::*parse_function_type)() const;  
    typedef const IValue& (ParserXBase::*parse_function_type)() const;  
    static const char_type *c_DefaultOprt[]; 
    static bool s_bDumpStack;
    static bool s_bDumpRPN;

  public:

    static string_type GetVersion();
    static void EnableDebugDump(bool bDumpCmd, bool bDumpRPN);

    ParserXBase(); 
    ParserXBase( const ParserXBase &a_Parser );
    ParserXBase& operator=(const ParserXBase &a_Parser);
    virtual ~ParserXBase();
    
    const IValue& Eval() const;

    void SetExpr(const string_type &a_sExpr);
    void AddValueReader(IValueReader *a_pReader);

    void AddPackage(IPackage *p);
    void RemovePackage(IPackage *p);

    void DefineFun(ICallback *a_pCallback);
    void DefineConst(const string_type &a_sName, const Value &a_Val);
    void DefineVar(const string_type &a_sName, const Variable &a_fVar);
    
    // adding operators
    void DefineOprt(IOprtBin *a_pCallback);
    void DefinePostfixOprt(IOprtPostfix *a_pCallback);
    void DefineInfixOprt(IOprtInfix *a_pCallback);

    // Clear user defined variables, constants or functions
    void ClearVar();
    void ClearFun();
    void ClearConst();
    void ClearInfixOprt();
    void ClearPostfixOprt();
    void ClearOprt();
    void DumpRPN() const;

    void RemoveVar(const string_type &a_sVarName);
    const var_maptype& GetExprVar() const;
    const var_maptype& GetVar() const;
    const val_maptype& GetConst() const;
    const fun_maptype& GetFunDef() const;
    const string_type& GetExpr() const;

    const char_type ** GetOprtDef() const;
    void DefineNameChars(const char_type *a_szCharset);
    void DefineOprtChars(const char_type *a_szCharset);
    void DefineInfixOprtChars(const char_type *a_szCharset);
    
    void EnableAutoCreateVar(bool bStat);
    void EnableOptimizer(bool bStat);
    bool IsAutoCreateVarEnabled() const;

    const char_type* ValidNameChars() const;
    const char_type* ValidOprtChars() const;
    const char_type* ValidInfixOprtChars() const;

    void  Error(EErrorCodes a_iErrc, 
                int a_iPos = -1,
                const IToken *a_pTok = 0) const;

  protected:

    void  CheckName(const string_type &a_sName, const string_type &a_CharSet) const;

    fun_maptype  m_FunDef;           ///< Function definitions
    oprt_pfx_maptype m_PostOprtDef;  ///< Postfix operator callbacks
    oprt_ifx_maptype m_InfixOprtDef; ///< Infix operator callbacks.
    oprt_bin_multimap m_OprtDef;     ///< Binary operator callbacks
    val_maptype  m_valConst;         ///< Definition of parser constants
    var_maptype  m_VarDef;           ///< user defind variables.

  private:

    void  ReInit() const;
    void  ClearExpr();
    void  CreateRPN() const;
    void  StackDump(const Stack<ptr_val_type> &a_stVal, 
                     const Stack<ptr_tok_type> &a_stOprt) const;

    void Assign(const ParserXBase &a_Parser);
    void InitTokenReader();

    void ApplyFunc(Stack<ptr_tok_type> &a_stOpt, Stack<ptr_val_type> &a_stVal, int a_iArgCount) const;
    void ApplyIfElse(Stack<ptr_tok_type> &a_stOpt, Stack<ptr_val_type> &a_stVal) const;
    void ApplyRemainingOprt(Stack<ptr_tok_type> &a_stOpt,
                                Stack<ptr_val_type> &a_stVal) const;
    const IValue& ParseFromString() const; 
    const IValue& ParseFromRPN() const; 

    /** \brief Pointer to the parser function. 
    

      Eval() calls the function whose address is stored there.
    */
    mutable parse_function_type m_pParserEngine;

    /** \brief Managed pointer to the token reader object. */
    std::auto_ptr<TokenReader> m_pTokenReader; 

    val_vec_type m_valDynVarShadow;  ///< Value objects referenced by variables created at parser runtime
    string_type m_sNameChars;        ///< Charset for names
    string_type m_sOprtChars;        ///< Charset for postfix/ binary operator tokens
    string_type m_sInfixOprtChars;   ///< Charset for infix operator tokens

    /** \brief Index of the final result in the stack array. 
    
      The parser supports expressions using with commas for seperating
      multiple expression. Each comma will increase this number.
      (i.e. "a=10,b=15,c=a*b")

    */
    mutable int m_nFinalResultIdx;          

    /** \brief A flag indicating querying of expression variables is underway.
      

      If this flag is set the parser is momentarily querying the expression 
      variables. In these cases undefined variable errors must be ignored cause 
      the whole point of querying the expression variables is for finding out 
      which variables mut be defined.

    */
    mutable bool m_bIsQueryingExprVar;    

    mutable bool m_bAutoCreateVar;      ///< If this flag is set unknown variables will be defined automatically

    mutable RPN m_rpn;                  ///< reverse polish notation
    mutable val_vec_type m_vStackBuffer;
    mutable ValueCache m_cache;         ///< A cache for recycling value items instead of deleting them

  };
} // namespace mu

#endif

