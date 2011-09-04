/** \file
    \brief This file contains the implementation of binary assignment 
           operators used in muParser.

<pre>
               __________                                 ____  ___
    _____  __ _\______   \_____ _______  ______ __________\   \/  /
   /     \|  |  \     ___/\__  \\_  __ \/  ___// __ \_  __ \     / 
  |  Y Y  \  |  /    |     / __ \|  | \/\___ \\  ___/|  | \/     \ 
  |__|_|  /____/|____|    (____  /__|  /____  >\___  >__| /___/\  \
        \/                     \/           \/     \/           \_/

  muParserX - A C++ math parser library with array and string support
  Copyright 2010 Ingo Berg

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU LESSER GENERAL PUBLIC LICENSE
  as published by the Free Software Foundation, either version 3 of 
  the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with this program.  If not, see http://www.gnu.org/licenses.
</pre>
*/
#include "mpOprtBinAssign.h"


MUP_NAMESPACE_START

  //---------------------------------------------------------------------
  //
  //  class OprtAssign
  //
  //---------------------------------------------------------------------

  OprtAssign::OprtAssign() 
    :IOprtBin(_T("="), (int)prASSIGN, oaLEFT)
  {}

  //---------------------------------------------------------------------
  const char_type* OprtAssign::GetDesc() const 
  { 
    return _T("'=' assignement operator"); 
  }

  //---------------------------------------------------------------------
  IToken* OprtAssign::Clone() const
  { 
    return new OprtAssign(*this); 
  }
  
  //---------------------------------------------------------------------
  void OprtAssign::Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int)
  {
    Variable *pVar = dynamic_cast<Variable*>(a_pArg[0].Get());

    // assigment to non variable type
    if (!pVar)
    {
      ErrorContext err;
      err.Arg   = 1;
      err.Ident = _T("=");
      err.Errc  = ecASSIGNEMENT_TO_VALUE;
      throw ParserError(err);
    }

    *pVar = *a_pArg[1]; //pVar->SetFloat(a_pArg[1]->GetFloat());
    *ret = *pVar; 
  }

  //---------------------------------------------------------------------
  //
  //  class OprtAssignAdd
  //
  //---------------------------------------------------------------------

  OprtAssignAdd::OprtAssignAdd() 
    :IOprtBin(_T("+="), (int)prASSIGN, oaLEFT) 
  {}

  //---------------------------------------------------------------------
  void OprtAssignAdd::Eval(ptr_val_type& ret, const ptr_val_type *a_pArg, int)   
  {
    Variable *pVar = dynamic_cast<Variable*>(a_pArg[0].Get());

    // assigment to non variable type
    if (!pVar)
    {
      ErrorContext err;
      err.Arg   = 1;
      err.Ident = _T("+=");
      err.Errc  = ecASSIGNEMENT_TO_VALUE;
      throw ParserError(err);
    }

    *pVar = cmplx_type(a_pArg[0]->GetFloat() + a_pArg[1]->GetFloat(),
                       a_pArg[0]->GetImag() + a_pArg[1]->GetImag());
    *ret = *pVar;
  }

  //---------------------------------------------------------------------
  const char_type* OprtAssignAdd::GetDesc() const 
  { 
    return _T("assignement operator"); 
  }

  //---------------------------------------------------------------------
  IToken* OprtAssignAdd::Clone() const            
  { 
    return new OprtAssignAdd(*this); 
  }

  //---------------------------------------------------------------------
  //
  //  class OprtAssignAdd
  //
  //---------------------------------------------------------------------

  OprtAssignSub::OprtAssignSub() 
    :IOprtBin(_T("-="), (int)prASSIGN, oaLEFT) 
  {}

  //---------------------------------------------------------------------
  void OprtAssignSub::Eval(ptr_val_type& ret, const ptr_val_type *a_pArg, int)   
  {
    Variable *pVar = dynamic_cast<Variable*>(a_pArg[0].Get());
    if (!pVar)
    {
      ErrorContext err;
      err.Arg   = 1;
      err.Ident = _T("-=");
      err.Errc  = ecASSIGNEMENT_TO_VALUE;
      throw ParserError(err);
    }

    *pVar = cmplx_type(a_pArg[0]->GetFloat() - a_pArg[1]->GetFloat(),
                       a_pArg[0]->GetImag() - a_pArg[1]->GetImag());
    *ret = *pVar; 
  }

  //---------------------------------------------------------------------
  const char_type* OprtAssignSub::GetDesc() const 
  { 
    return _T("assignement operator"); 
  }

  //---------------------------------------------------------------------
  IToken* OprtAssignSub::Clone() const            
  { 
     return new OprtAssignSub(*this); 
  }

  //---------------------------------------------------------------------
  //
  //  class OprtAssignAdd
  //
  //---------------------------------------------------------------------

  OprtAssignMul::OprtAssignMul() 
    :IOprtBin(_T("*="), (int)prASSIGN, oaLEFT) 
  {}

  //---------------------------------------------------------------------
  void OprtAssignMul::Eval(ptr_val_type& ret, const ptr_val_type *a_pArg, int)
  {
    Variable *pVar = dynamic_cast<Variable*>(a_pArg[0].Get());
    if (!pVar)
    {
      ErrorContext err;
      err.Arg   = 1;
      err.Ident = _T("*=");
      err.Errc  = ecASSIGNEMENT_TO_VALUE;
      throw ParserError(err);
    }

    float_type a = a_pArg[0]->GetFloat(),
               b = a_pArg[0]->GetImag(),
               c = a_pArg[1]->GetFloat(),
               d = a_pArg[1]->GetImag();
    *pVar = cmplx_type(a*c-b*d, a*d-b*c); 
    *ret = *pVar;
  }

  //---------------------------------------------------------------------
  const char_type* OprtAssignMul::GetDesc() const 
  { 
    return _T("multiply and assign operator"); 
  }

  //---------------------------------------------------------------------
  IToken* OprtAssignMul::Clone() const
  {  
    return new OprtAssignMul(*this); 
  }

  //---------------------------------------------------------------------
  //
  //  class OprtAssignDiv
  //
  //---------------------------------------------------------------------

  OprtAssignDiv::OprtAssignDiv() : IOprtBin(_T("/="), (int)prASSIGN, oaLEFT) 
  {}

  //------------------------------------------------------------------------------
  void OprtAssignDiv::Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int)
  {
    Variable *pVar = dynamic_cast<Variable*>(a_pArg[0].Get());
    if (!pVar)
    {
      ErrorContext err;
      err.Arg   = 1;
      err.Ident = _T("/=");
      err.Errc  = ecASSIGNEMENT_TO_VALUE;
      throw ParserError(err);
    }

    float_type a = a_pArg[0]->GetFloat(),
               b = a_pArg[0]->GetImag(),
               c = a_pArg[1]->GetFloat(),
               d = a_pArg[1]->GetImag(),
               n = c*c + d*d;
    *pVar = cmplx_type((a*c+b*d)/n, (b*c-a*d)/n); 
    *ret = *pVar; 
  }

  //------------------------------------------------------------------------------
  const char_type* OprtAssignDiv::GetDesc() const 
  { 
     return _T("multiply and divide operator"); 
  }

  //------------------------------------------------------------------------------
  IToken* OprtAssignDiv::Clone() const
  {  
    return new OprtAssignDiv(*this); 
  }
MUP_NAMESPACE_END
