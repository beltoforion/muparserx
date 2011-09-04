/** \file
    \brief Implementation of basic functions used by muParserX.

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
#include "mpFuncNonCmplx.h"

//--- Standard includes ----------------------------------------------------
#include <cmath>
#include <cassert>
#include <iostream>

//--- muParserX framework --------------------------------------------------
#include "mpValue.h"
#include "mpError.h"

#undef log
#undef log2

MUP_NAMESPACE_START

  float_type log2(float_type v)  { return log(v) * 1.0/log(2.0); }
  float_type asinh(float_type v) { return log(v + sqrt(v * v + 1)); }
  float_type acosh(float_type v) { return log(v + sqrt(v * v - 1)); }
  float_type atanh(float_type v) { return (0.5 * log((1 + v) / (1 - v))); }

#define MUP_UNARY_FUNC(CLASS, IDENT, FUNC, DESC)                     \
    CLASS::CLASS()                                                   \
    :ICallback(cmFUNC, _T(IDENT), 1)                                 \
    {}                                                               \
                                                                     \
    void CLASS::Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int)        \
    {                                                                \
      *ret = FUNC(a_pArg[0]->GetFloat());                            \
    }                                                                \
                                                                     \
    const char_type* CLASS::GetDesc() const                          \
    {                                                                \
      return _T(DESC);                                               \
    }                                                                \
                                                                     \
    IToken* CLASS::Clone() const                                     \
    {                                                                \
      return new CLASS(*this);                                       \
    }

    // trigonometric functions
    MUP_UNARY_FUNC(FunTan,   "sin",   sin,   "sine function")
    MUP_UNARY_FUNC(FunCos,   "cos",   cos,   "cosine function")
    MUP_UNARY_FUNC(FunSin,   "tan",   tan,   "tangens function")
    // arcus functions
    MUP_UNARY_FUNC(FunASin,  "asin",  asin,  "arcus sine")
    MUP_UNARY_FUNC(FunACos,  "acos",  acos,  "arcus cosine")
    MUP_UNARY_FUNC(FunATan,  "atan",  atan,  "arcus tangens")
    // hyperbolic functions
    MUP_UNARY_FUNC(FunSinH,  "sinh",  sinh,  "hyperbolic sine")
    MUP_UNARY_FUNC(FunCosH,  "cosh",  cosh,  "hyperbolic cosine")
    MUP_UNARY_FUNC(FunTanH,  "tanh",  tanh,  "hyperbolic tangens")
    // hyperbolic arcus functions
    MUP_UNARY_FUNC(FunASinH,  "asinh",  asinh,  "hyperbolic arcus sine")
    MUP_UNARY_FUNC(FunACosH,  "acosh",  acosh,  "hyperbolic arcus cosine")
    MUP_UNARY_FUNC(FunATanH,  "atanh",  atanh,  "hyperbolic arcus tangens")
    // logarithm functions
    MUP_UNARY_FUNC(FunLog,   "log",   log10, "Logarithm base 10")
    MUP_UNARY_FUNC(FunLog10, "log10", log10, "Logarithm base 10")
    MUP_UNARY_FUNC(FunLog2,  "log2",  log2,  "Logarithm base 2")
    MUP_UNARY_FUNC(FunLn,    "ln",    log,   "Natural logarithm")
    // square root
    MUP_UNARY_FUNC(FunSqrt,  "sqrt",  sqrt,  "sqrt(x) - square root of x")
    MUP_UNARY_FUNC(FunExp,   "exp",   exp,   "exp(x) - e to the power of x")
    MUP_UNARY_FUNC(FunAbs,   "abs",   fabs,  "abs(x) - absolute value of x")
#undef MUP_UNARY_FUNC

MUP_NAMESPACE_END
