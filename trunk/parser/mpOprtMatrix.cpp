/*
               __________                                 ____  ___
    _____  __ _\______   \_____ _______  ______ __________\   \/  /
   /     \|  |  \     ___/\__  \\_  __ \/  ___// __ \_  __ \     / 
  |  Y Y  \  |  /    |     / __ \|  | \/\___ \\  ___/|  | \/     \ 
  |__|_|  /____/|____|    (____  /__|  /____  >\___  >__| /___/\  \
        \/                     \/           \/     \/           \_/
                                       Copyright (C) 2013 Ingo Berg
                                       All rights reserved.

  muParserX - A C++ math parser library with array and string support
  Copyright (c) 2013, Ingo Berg
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
#include "mpOprtMatrix.h"


MUP_NAMESPACE_START

//-------------------------------------------------------------------------------------------------
//
//  class  OprtTranspose
//
//-------------------------------------------------------------------------------------------------

  OprtTranspose::OprtTranspose(IPackage* /*pPackage*/)
    :IOprtPostfix(_T("'"))
  {}

  //-------------------------------------------------------------------------------------------------
  void OprtTranspose::Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int /*a_iArgc*/)
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
// class OprtColon
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

    int n = (int)(argMax->GetFloat() - argMin->GetFloat()) + 1;
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
