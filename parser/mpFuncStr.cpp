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
#include "mpFuncStr.h"

#include <cmath>
#include <cassert>
#include <cstdio>
#include <cwchar>
#include <algorithm>

#include "mpValue.h"
#include "mpError.h"


MUP_NAMESPACE_START

  //------------------------------------------------------------------------------
  //
  // Strlen function
  //
  //------------------------------------------------------------------------------

  FunStrLen::FunStrLen()
    :ICallback(cmFUNC, _T("strlen"), 1)
  {}

  //------------------------------------------------------------------------------
  void FunStrLen::Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int)
  {
    string_type str = a_pArg[0]->GetString();
    *ret = (int)str.length();
  }

  //------------------------------------------------------------------------------
  const char_type* FunStrLen::GetDesc() const
  {
    return _T("strlen(s) - Returns the length of the string s.");
  }

  //------------------------------------------------------------------------------
  IToken* FunStrLen::Clone() const
  {
    return new FunStrLen(*this);
  }

  //------------------------------------------------------------------------------
  //
  // ToUpper function
  //
  //------------------------------------------------------------------------------

  FunStrToUpper::FunStrToUpper()
    :ICallback(cmFUNC, _T("toupper"), 1)
  {}

  //------------------------------------------------------------------------------
  void FunStrToUpper::Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int)
  {
    using namespace std;

    string_type str = a_pArg[0]->GetString();
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);

    *ret = str;
  }

  //------------------------------------------------------------------------------
  const char_type* FunStrToUpper::GetDesc() const
  {
    return _T("toupper(s) - Converts the string s to uppercase characters.");
  }

  //------------------------------------------------------------------------------
  IToken* FunStrToUpper::Clone() const
  {
    return new FunStrToUpper(*this);
  }

  //------------------------------------------------------------------------------
  //
  // String to double conversion
  //
  //------------------------------------------------------------------------------

  FunStrToDbl::FunStrToDbl()
    :ICallback(cmFUNC, _T("str2dbl"), 1)
  {}

  //------------------------------------------------------------------------------
  void FunStrToDbl::Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc)
  {
    assert(a_iArgc==1);
    string_type in;
    float_type out;

    in = a_pArg[0]->GetString();
    
#ifndef _UNICODE    
    sscanf(in.c_str(), "%lf", &out);
#else
    swscanf(in.c_str(), _T("%lf"), &out);
#endif

    *ret = out;
  }

  //------------------------------------------------------------------------------
  const char_type* FunStrToDbl::GetDesc() const
  {
    return _T("str2dbl(s) - Converts the string stored in s into a floating foint value.");
  }

  //------------------------------------------------------------------------------
  IToken* FunStrToDbl::Clone() const
  {
    return new FunStrToDbl(*this);
  }
}  // namespace mu
