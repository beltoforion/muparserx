/*
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
*/
#include "mpOprtMatrix.h"


MUP_NAMESPACE_START

//-------------------------------------------------------------------------------------------------
//
//  class  OprtTranspose
//
//-------------------------------------------------------------------------------------------------

  OprtTranspose::OprtTranspose(IPackage* pPackage)
    :IOprtPostfix(_T("'"))
  {}

  //-------------------------------------------------------------------------------------------------
  void OprtTranspose::Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc)
  {
    if (a_pArg[0]->IsMatrix())
    {
      matrix_type matrix = a_pArg[0]->GetArray();
      matrix.Transpose();
     *ret = matrix;
    }
    else
      *ret = *a_pArg[0];
  }

  //-------------------------------------------------------------------------------------------------
  const char_type* OprtTranspose::GetDesc() const
  {
    return _T("foo' - An operator for transposing a matrix.");
  }

  //-------------------------------------------------------------------------------------------------
  IToken* OprtTranspose::Clone() const
  {
    return new OprtTranspose(*this); 
  }

//-----------------------------------------------------------
//
// class OprtAdd
//
//-----------------------------------------------------------

  OprtColon::OprtColon() 
    :IOprtBin(_T("~"), (int)prCOLON, oaLEFT) 
  {}

  //-----------------------------------------------------------
  void OprtColon::Eval(ptr_val_type& ret, const ptr_val_type *a_pArg, int num)
  { 
    assert(num==2);

    const IValue *argMin = a_pArg[0].Get();
    const IValue *argMax = a_pArg[1].Get();
  
    if (!argMin->IsNonComplexScalar())
      throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), argMin->GetType(), 'i', 1)); 

    if (!argMax->IsNonComplexScalar())
      throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), argMax->GetType(), 'i', 1)); 

    if (*argMax < *argMin)
      throw ParserError(_T("Colon operator: Maximum value smaller than Minimum!")); 

    int n = (argMax->GetFloat() - argMin->GetFloat()) + 1;
    matrix_type arr(n);
    for (int i=0; i<n; ++i)
      arr.At(i) = argMin->GetFloat() + i;

    *ret = arr; 
  }

  //-----------------------------------------------------------
  const char_type* OprtColon::GetDesc() const 
  { 
    return _T(": - Colon operator"); 
  }
  
  //-----------------------------------------------------------
  IToken* OprtColon::Clone() const
  { 
    return new OprtColon(*this); 
  }
MUP_NAMESPACE_END
