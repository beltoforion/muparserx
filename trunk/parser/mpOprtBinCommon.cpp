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
#include "mpOprtBinCommon.h"

MUP_NAMESPACE_START

  //-----------------------------------------------------------
  //
  // class OprtAnd
  //
  //-----------------------------------------------------------

  OprtAnd::OprtAnd() 
    :IOprtBin(_T("&"), (int)prBIT_AND, oaLEFT) 
  {}

  //-----------------------------------------------------------
  void OprtAnd::Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int num)
  { 
    assert(num==2);

    if (!a_pArg[0]->IsScalar())
      throw ParserError(ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a_pArg[0]->GetType(), 'i', 1));
    
    if (!a_pArg[1]->IsScalar())
      throw ParserError(ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a_pArg[1]->GetType(), 'i', 2));

    float_type a = a_pArg[0]->GetFloat(),
               b = a_pArg[1]->GetFloat();

    if (a!=(int_type)a)
      throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, a_pArg[0]->GetIdent(), a_pArg[0]->GetType(), 'i', 1) ); 
    
    if (b!=(int_type)b)
      throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, a_pArg[1]->GetIdent(), a_pArg[1]->GetType(), 'i', 2) ); 

    *ret = (int_type)a & (int_type)(b); 
  }

  //-----------------------------------------------------------
  const char_type* OprtAnd::GetDesc() const 
  { 
    return _T("bitwise and"); 
  }
  
  //-----------------------------------------------------------
  IToken* OprtAnd::Clone() const
  { 
    return new OprtAnd(*this); 
  }

  //-----------------------------------------------------------
  //
  // class OprtOr
  //
  //-----------------------------------------------------------

  OprtOr::OprtOr() 
    :IOprtBin(_T("|"), (int)prBIT_OR, oaLEFT) 
  {}

  //-----------------------------------------------------------
  void OprtOr::Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int num)
  { 
    assert(num==2);

    if (!a_pArg[0]->IsScalar())
      throw ParserError(ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a_pArg[0]->GetType(), 'i', 1));
    
    if (!a_pArg[1]->IsScalar())
      throw ParserError(ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a_pArg[1]->GetType(), 'i', 2));

    float_type a = a_pArg[0]->GetFloat(),
               b = a_pArg[1]->GetFloat();

    if (a!=(int_type)a)
      throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, a_pArg[0]->GetIdent(), a_pArg[0]->GetType(), 'i', 1) ); 
    
    if (b!=(int_type)b)
      throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, a_pArg[1]->GetIdent(), a_pArg[1]->GetType(), 'i', 2) ); 

    *ret = (int_type)a | (int_type)(b); 
  }

  //-----------------------------------------------------------
  const char_type* OprtOr::GetDesc() const 
  { 
    return _T("bitwise or"); 
  }
  
  //-----------------------------------------------------------
  IToken* OprtOr::Clone() const
  { 
    return new OprtOr(*this); 
  }

  //-----------------------------------------------------------
  //
  // class OprtLOr
  //
  //-----------------------------------------------------------

  OprtLOr::OprtLOr() 
    :IOprtBin(_T("||"), (int)prLOGIC_OR, oaLEFT) 
  {}

  //-----------------------------------------------------------
  void OprtLOr::Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int num)
  { 
    assert(num==2);
    *ret = a_pArg[0]->GetBool() || a_pArg[1]->GetBool(); 
  }

  //-----------------------------------------------------------
  const char_type* OprtLOr::GetDesc() const 
  { 
    return _T("logical or"); 
  }
  
  //-----------------------------------------------------------
  IToken* OprtLOr::Clone() const
  { 
    return new OprtLOr(*this); 
  }

  //-----------------------------------------------------------
  //
  // class OprtLAnd
  //
  //-----------------------------------------------------------

  OprtLAnd::OprtLAnd() 
    :IOprtBin(_T("&&"), (int)prLOGIC_AND, oaLEFT) 
  {}

  //-----------------------------------------------------------
  void OprtLAnd::Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int num)
  { 
    assert(num==2);
    *ret = a_pArg[0]->GetBool() && a_pArg[1]->GetBool(); 
  }

  //-----------------------------------------------------------
  const char_type* OprtLAnd::GetDesc() const 
  { 
    return _T("logical and"); 
  }
  
  //-----------------------------------------------------------
  IToken* OprtLAnd::Clone() const
  { 
    return new OprtLAnd(*this); 
  }

  //-----------------------------------------------------------
  //
  // class OprtShl
  //
  //-----------------------------------------------------------

  OprtShl::OprtShl() 
    :IOprtBin(_T("<<"), (int)prSHIFT, oaLEFT) 
  {}

  //-----------------------------------------------------------
  void OprtShl::Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int num)
  { 
    assert(num==2);

    if (!a_pArg[0]->IsScalar())
      throw ParserError(ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a_pArg[0]->GetType(), 'i', 1));
    
    if (!a_pArg[1]->IsScalar())
      throw ParserError(ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a_pArg[1]->GetType(), 'i', 2));

    float_type a = a_pArg[0]->GetFloat(),
               b = a_pArg[1]->GetFloat();

    if (a!=(int_type)a)
      throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, a_pArg[0]->GetIdent(), a_pArg[0]->GetType(), 'i', 1) ); 
    
    if (b!=(int_type)b)
      throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, a_pArg[1]->GetIdent(), a_pArg[1]->GetType(), 'i', 2) ); 


    *ret = (int_type)a << (int_type)(b); 
  }

  //-----------------------------------------------------------
  const char_type* OprtShl::GetDesc() const 
  { 
    return _T("shift left"); 
  }
  
  //-----------------------------------------------------------
  IToken* OprtShl::Clone() const
  { 
    return new OprtShl(*this); 
  }

  //-----------------------------------------------------------
  //
  // class OprtShr
  //
  //-----------------------------------------------------------

  OprtShr::OprtShr() 
    :IOprtBin(_T(">>"), (int)prSHIFT, oaLEFT) 
  {}

  //-----------------------------------------------------------
  void OprtShr::Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int num)
  { 
    assert(num==2);

    if (!a_pArg[0]->IsScalar())
      throw ParserError(ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a_pArg[0]->GetType(), 'i', 1));
    
    if (!a_pArg[1]->IsScalar())
      throw ParserError(ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a_pArg[1]->GetType(), 'i', 2));

    float_type a = a_pArg[0]->GetFloat(),
               b = a_pArg[1]->GetFloat();

    if (a!=(int_type)a)
      throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, a_pArg[0]->GetIdent(), a_pArg[0]->GetType(), 'i', 1) ); 
    
    if (b!=(int_type)b)
      throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, a_pArg[1]->GetIdent(), a_pArg[1]->GetType(), 'i', 2) ); 

    *ret = (int_type)a >> (int_type)b; 
  }

  //-----------------------------------------------------------
  const char_type* OprtShr::GetDesc() const 
  { 
    return _T("shift left"); 
  }
  
  //-----------------------------------------------------------
  IToken* OprtShr::Clone() const
  { 
    return new OprtShr(*this); 
  }

  //------------------------------------------------------------------------------
  //
  //  Cast To Float
  //
  //------------------------------------------------------------------------------

  OprtCastToFloat::OprtCastToFloat()
    :IOprtInfix( _T("(float)"))
  {}

  //------------------------------------------------------------------------------
  void OprtCastToFloat::Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int /*a_iArgc*/)  
  { 
    switch(a_pArg[0]->GetType())
    {
    case 'i':
    case 'f':  
    case 'b':  
         *ret = a_pArg[0]->GetFloat(); 
         break;

    default:
      {
        ErrorContext err;
        err.Errc = ecINVALID_TYPECAST;
        err.Type1 = a_pArg[0]->GetType();
        err.Type2 = 'f';
        throw ParserError(err);
      } 
    } // switch value type
  }

  //------------------------------------------------------------------------------
  const char_type* OprtCastToFloat::GetDesc() const 
  { 
    return _T("cast a value into a floating point number"); 
  }

  //------------------------------------------------------------------------------
  IToken* OprtCastToFloat::Clone() const 
  { 
    return new OprtCastToFloat(*this); 
  }


  //------------------------------------------------------------------------------
  //
  //  Cast To Int
  //
  //------------------------------------------------------------------------------

  OprtCastToInt::OprtCastToInt()
    :IOprtInfix( _T("(int)"))
  {}

  //------------------------------------------------------------------------------
  void OprtCastToInt::Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int /*a_iArgc*/)  
  { 
    switch(a_pArg[0]->GetType())
    {
    case 'f':  
    case 'i': 
    case 'b':  
         *ret = (int_type)a_pArg[0]->GetFloat();
         break;

    default:
      {
        ErrorContext err;
        err.Errc = ecINVALID_TYPECAST;
        err.Type1 = a_pArg[0]->GetType();
        err.Type2 = 'i';
        throw ParserError(err);
      } 
    } // switch value type
  }

  //------------------------------------------------------------------------------
  const char_type* OprtCastToInt::GetDesc() const 
  { 
    return _T("cast a value into a floating point number"); 
  }

  //------------------------------------------------------------------------------
  IToken* OprtCastToInt::Clone() const 
  { 
    return new OprtCastToInt(*this); 
  }
}
