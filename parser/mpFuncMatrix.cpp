/** \file
    \brief Definition of functions for complex valued operations.

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
