/*
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
*/
#ifndef MP_OPRT_BIN_H
#define MP_OPRT_BIN_H

/** \file 
    \brief Definitions of classes used as callbacks for standard binary operators. 
*/

/** \defgroup binop Binary operator callbacks

  This group lists the objects representing the binary operators of muParserX.
*/

#include <cmath>
#include "mpIOprt.h"
#include "mpValue.h"
#include "mpError.h"


MUP_NAMESPACE_START

#define MUP_NAME_PROXY_get_float_type  GetFloat
#define MUP_NAME_PROXY_get_string_type GetString
#define MUP_NAME_PROXY_get_bool_type   GetBool
#define MUP_NAME_PROXY_get_value_type  

/** \brief MUP_BINARY_OPERATOR(CLASS, IDENT, PROT, TYPE, DESC, PRI, OP)
    \param CLASS Name of the class to be defined
    \param IDENT The string to be used as the operator identifier
    \param PROT A string representing the operators prototype
    \param TYPE The datatype used for the operation
    \param DESC A string containing the operator description
    \param PRI The operator precedence
    \param OP The operation to perform

    A macro for simplifying the process of creating binary operator 
    callback classes. 
*/
#define MUP_BINARY_OPERATOR(CLASS, IDENT, TYPE, DESC, PRI, ASC, OP)        \
  class CLASS : public IOprtBin                                            \
  {                                                                        \
  public:                                                                  \
    CLASS() : IOprtBin((IDENT), (PRI), (ASC)) {}                           \
                                                                           \
    virtual void Eval(ptr_val_type& ret, const ptr_val_type *arg, int argc)\
    {                                                                      \
      assert(argc==2);                                                     \
      TYPE a = arg[0]->MUP_NAME_PROXY_get_##TYPE();                        \
      TYPE b = arg[1]->MUP_NAME_PROXY_get_##TYPE();                        \
      *ret = OP;                                                           \
    }                                                                      \
                                                                           \
    virtual const char_type* GetDesc() const { return (DESC); }            \
    virtual IToken* Clone() const            { return new CLASS(); }       \
  }; 

  // for string values
  MUP_BINARY_OPERATOR(OprtStrAdd, _T("//"), string_type, _T(""), 2, oaLEFT, a+b)
  // logical operators
  MUP_BINARY_OPERATOR(OprtBAnd, _T("and"),  bool_type, _T("less than"), 1, oaLEFT, a&&b)
  MUP_BINARY_OPERATOR(OprtBOr,  _T("or"),  bool_type, _T("less than"), 1, oaLEFT, a||b)
  MUP_BINARY_OPERATOR(OprtBXor, _T("xor"),  bool_type, _T("less than"), 1, oaLEFT, (bool_type)(a^b))

//#undef MUP_NAME_PROXY_get_float_type
//#undef MUP_NAME_PROXY_get_string_type
//#undef MUP_NAME_PROXY_get_bool_type
//#undef MUP_BINARY_OPERATOR

  //------------------------------------------------------------------------------
  /** \brief Callback object for testing if two values are equal.
      \ingroup binop
  */
  class OprtEQ : public IOprtBin    
  {
  public:
    OprtEQ() : IOprtBin(_T("=="), 2, oaLEFT) {}
    virtual void Eval(ptr_val_type& ret, const ptr_val_type *a_pArg, int)
    { 
      *ret = *a_pArg[0] == *a_pArg[1]; 
    }
    virtual const char_type* GetDesc() const { return _T("equals operator"); }
    virtual IToken* Clone() const            { return new OprtEQ; }
  };


  //------------------------------------------------------------------------------
  /** \brief Callback object for testing if two values are not equal.
      \ingroup binop
  */
  class OprtNEQ : public IOprtBin    
  {
  public:
    OprtNEQ() : IOprtBin(_T("!="), 2, oaLEFT) {}
    virtual void Eval(ptr_val_type& ret, const ptr_val_type *a_pArg, int)
    { 
      *ret = *a_pArg[0] != *a_pArg[1]; 
    }

    virtual const char_type* GetDesc() const { return _T("neq operator"); }
    virtual IToken* Clone() const            { return new OprtNEQ; }
  };

  //------------------------------------------------------------------------------
  /** \brief Callback object class for the "Less than" operator.
      \ingroup binop
  */
  class OprtLT : public IOprtBin    
  {
  public:
    OprtLT() : IOprtBin(_T("<"), 2, oaLEFT) {}
    virtual void Eval(ptr_val_type& ret, const ptr_val_type *a_pArg, int)
    { 
       *ret = *a_pArg[0] < *a_pArg[1];
    }

    virtual const char_type* GetDesc() const { return _T("less operator"); }
    virtual IToken* Clone() const            { return new OprtLT; }
  };

  //------------------------------------------------------------------------------
  /** \brief Callback object class for the "Greater than" operator.
      \ingroup binop
  */
  class OprtGT : public IOprtBin    
  {
  public:
    OprtGT() : IOprtBin(_T(">"), 2, oaLEFT) {}
    virtual void Eval(ptr_val_type& ret, const ptr_val_type *a_pArg, int)
    { 
       *ret = *a_pArg[0] > *a_pArg[1]; 
    }

    virtual const char_type* GetDesc() const { return _T("greater than"); }
    virtual IToken* Clone() const            { return new OprtGT; }
  };

  //------------------------------------------------------------------------------
  /** \brief Callback object class for the "Less or equal" operator.
      \ingroup binop
  */
  class OprtLE : public IOprtBin    
  {
  public:
    OprtLE() : IOprtBin(_T("<="), 2, oaLEFT) {}
    virtual void Eval(ptr_val_type& ret, const ptr_val_type *a_pArg, int)
    { 
      *ret = *a_pArg[0] <= *a_pArg[1];
    }

    virtual const char_type* GetDesc() const { return _T("less or equal operator"); }
    virtual IToken* Clone() const            { return new OprtLE; }
  };

  //------------------------------------------------------------------------------
  /** \brief Callback object class for the "Greater or or equal" operator.
      \ingroup binop
  */
  class OprtGE : public IOprtBin    
  {
  public:
    OprtGE() : IOprtBin(_T(">="), 2, oaLEFT) {}
    virtual void Eval(ptr_val_type& ret, const ptr_val_type *a_pArg, int)
    { 
       *ret = *a_pArg[0] >= *a_pArg[1]; 
    }

    virtual const char_type* GetDesc() const { return _T("greater or equal operator"); }
    virtual IToken* Clone() const            { return new OprtGE; }
  };

  //------------------------------------------------------------------------------
  /** \brief Callback class for a logic and operator.
      \ingroup binop
  */
  class OprtAnd : public IOprtBin    
  {
  public:
    OprtAnd();
    virtual void Eval(ptr_val_type& ret, const ptr_val_type *a_pArg, int);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  };

  //------------------------------------------------------------------------------
  /** \brief Callback class for a logic or operator.
      \ingroup binop
  */
  class OprtOr : public IOprtBin    
  {
  public:
    OprtOr();
    virtual void Eval(ptr_val_type& ret, const ptr_val_type *a_pArg, int);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  };

  //------------------------------------------------------------------------------
  /** \brief Callback class for a logical or operator.
      \ingroup binop
  */
  class OprtLOr : public IOprtBin    
  {
  public:
    OprtLOr();
    virtual void Eval(ptr_val_type& ret, const ptr_val_type *a_pArg, int);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  };

  //------------------------------------------------------------------------------
  /** \brief Callback class for a logical and operator.
      \ingroup binop
  */
  class OprtLAnd : public IOprtBin    
  {
  public:
    OprtLAnd();
    virtual void Eval(ptr_val_type& ret, const ptr_val_type *a_pArg, int);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  };

  //------------------------------------------------------------------------------
  /** \brief Callback class for the shift left operator.
      \ingroup binop
  */
  class OprtShl : public IOprtBin    
  {
  public:
    OprtShl();
    virtual void Eval(ptr_val_type& ret, const ptr_val_type *a_pArg, int);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  };

  //------------------------------------------------------------------------------
  /** \brief Callback class for the shift right operator.
      \ingroup binop
  */
  class OprtShr : public IOprtBin    
  {
  public:
    OprtShr();
    virtual void Eval(ptr_val_type& ret, const ptr_val_type *a_pArg, int);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  };

  //---------------------------------------------------------------------------
  /** \brief Callback for an operator allowing to cast values to floating 
             point values.
      \ingroup infix
  */
  class OprtCastToFloat : public IOprtInfix
  {
  public:
    OprtCastToFloat();
    virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  }; // class OprtCastToFloat

  //---------------------------------------------------------------------------
  /** \brief Callback for an operator allowing to cast values to integer values.
      \ingroup infix
  */
  class OprtCastToInt : public IOprtInfix
  {
  public:
    OprtCastToInt();
    virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  }; // class OprtCastToInt
}  // namespace mu

#endif
