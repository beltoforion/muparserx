/** \file
    \brief Definition of functions for complex valued operations.

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
#include "mpFuncMatrix.h"

//--- Standard includes ----------------------------------------------------
#include <cmath>
#include <cassert>
#include <complex>
#include <iostream>

//--- Parser framework -----------------------------------------------------
#include "mpValue.h"
#include "mpError.h"


MUP_NAMESPACE_START

  //-----------------------------------------------------------------------
  //
  //  class FunMatrixOnes
  //
  //-----------------------------------------------------------------------

  FunMatrixOnes::FunMatrixOnes(IPackage *package)
    :ICallback(cmFUNC, _T("ones"), -1, package)
  {}

  //-----------------------------------------------------------------------
  FunMatrixOnes::~FunMatrixOnes()
  {}

  //-----------------------------------------------------------------------
  void FunMatrixOnes::Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int argc)
  {
    switch(argc)
    {
    case 1: // Return a vector
            {
              int m = a_pArg[0]->GetInteger();
              if (m==1)
                *ret = 1.0;
              else
                *ret = matrix_type(a_pArg[0]->GetInteger(), 1, 1.0);
            }
            break;

    case 2: // Return a matrix
            {
              int m = a_pArg[0]->GetInteger(),
                  n = a_pArg[1]->GetInteger();

              if (m==n && m==1)
                *ret = 1.0;
              else
                *ret = matrix_type(a_pArg[0]->GetInteger(), a_pArg[1]->GetInteger(), 1.0);
            }
            break;
    
    default:
            ErrorContext err;
            err.Errc = ecINVALID_NUMBER_OF_PARAMETERS;
            err.Arg = 2;
            err.Ident = GetIdent();
            throw ParserError(err);
    }
  }

  //-----------------------------------------------------------------------
  const char_type* FunMatrixOnes::GetDesc() const
  {
    return _T("ones(x [, y]) - Returns a matrix whose elements are all 1.");
  }

  //-----------------------------------------------------------------------
  IToken* FunMatrixOnes::Clone() const
  {
    return new FunMatrixOnes(*this);
  }

MUP_NAMESPACE_END
