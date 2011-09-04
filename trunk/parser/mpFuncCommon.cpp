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
#include "mpFuncCommon.h"

#include <cassert>
#include <string>
#include <iostream>

#include "mpValue.h"
#include "mpParserBase.h"


MUP_NAMESPACE_START

  //------------------------------------------------------------------------------
  //
  // FunParserID
  //
  //------------------------------------------------------------------------------

  FunParserID::FunParserID()
    :ICallback(cmFUNC, _T("parserid"), 0)
  {}

  //------------------------------------------------------------------------------
  /** \brief Returns the number of elements stored in the first parameter. */
  void FunParserID::Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc)
  {
    ParserXBase &parser = *GetParent();
    string_type sVer = _T("muParserX V") + parser.GetVersion();
    *ret = sVer;
  }

  //------------------------------------------------------------------------------
  const char_type* FunParserID::GetDesc() const
  {
    return _T("parserid() - muParserX version information");
  }

  //------------------------------------------------------------------------------
  IToken* FunParserID::Clone() const
  {
    return new FunParserID(*this);
  }

  //------------------------------------------------------------------------------
  //
  // Max Function
  //
  //------------------------------------------------------------------------------

  FunMax::FunMax() : ICallback(cmFUNC, _T("max"), -1)
  {}

  //------------------------------------------------------------------------------
  void FunMax::Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc)
  {
    float_type max(-1e30), val;
    for (int i=0; i<a_iArgc; ++i)
    {
      switch(a_pArg[i]->GetType())
      {
      case 'f': val = a_pArg[i]->GetFloat();   break;
      case 'i': val = a_pArg[i]->GetFloat(); break;
      case 'n': break; // ignore not in list entries (missing parameter)
      case 'c':
      default:
        {
          ErrorContext err;
          err.Errc = ecTYPE_CONFLICT_FUN;
          err.Arg = i+1;
          err.Type1 = a_pArg[i]->GetType();
          err.Type2 = 'f';
          throw ParserError(err);
        }
      }
      max = std::max(max, val);    
    }
    
    *ret = max;
  }

  //------------------------------------------------------------------------------
  const char_type* FunMax::GetDesc() const
  {
    return _T("max(x,y,...,z) - Returns the maximum value from all of its function arguments.");
  }

  //------------------------------------------------------------------------------
  IToken* FunMax::Clone() const
  {
    return new FunMax(*this);
  }

  //------------------------------------------------------------------------------
  //
  // Min Function
  //
  //------------------------------------------------------------------------------

  FunMin::FunMin() : ICallback(cmFUNC, _T("min"), -1)
  {}

  //------------------------------------------------------------------------------
  /** \brief Returns the minimum value of all values. 
      \param a_pArg Pointer to an array of Values
      \param a_iArgc Number of values stored in a_pArg
  */
  void FunMin::Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc)
  {
    float_type min(1e30), val(min);

    for (int i=0; i<a_iArgc; ++i)
    {
      switch(a_pArg[i]->GetType())
      {
      case 'f': 
      case 'i': val = a_pArg[i]->GetFloat();   break;
      default:
        {
          ErrorContext err;
          err.Errc = ecTYPE_CONFLICT_FUN;
          err.Arg = i+1;
          err.Type1 = a_pArg[i]->GetType();
          err.Type2 = 'f';
          throw ParserError(err);
        }
      }
      min = std::min(min, val);    
    }
    
    *ret = min;
  }

  //------------------------------------------------------------------------------
  const char_type* FunMin::GetDesc() const
  {
    return _T("min(x,y,...,z) - Returns the minimum value from all of its function arguments.");
  }

  //------------------------------------------------------------------------------
  IToken* FunMin::Clone() const
  {
    return new FunMin(*this);
  }

  //------------------------------------------------------------------------------
  //
  // class FunSum
  //
  //------------------------------------------------------------------------------

  FunSum::FunSum() 
    :ICallback(cmFUNC, _T("sum"), -1)
  {}

  //------------------------------------------------------------------------------
  /** \brief Returns the minimum value of all values. 
      \param a_pArg Pointer to an array of Values
      \param a_iArgc Number of values stored in a_pArg
  */
  void FunSum::Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc)
  {
    float_type sum(0);

    for (int i=0; i<a_iArgc; ++i)
    {
      switch(a_pArg[i]->GetType())
      {
      case 'f': 
      case 'i': sum += a_pArg[i]->GetFloat();   break;
      default:
        {
          ErrorContext err;
          err.Errc = ecTYPE_CONFLICT_FUN;
          err.Arg = i+1;
          err.Type1 = a_pArg[i]->GetType();
          err.Type2 = 'f';
          throw ParserError(err);
        }
      }
    }
    
    *ret = sum;
  }

  //------------------------------------------------------------------------------
  const char_type* FunSum::GetDesc() const
  {
    return _T("sum(x,y,...,z) - Returns the sum of all arguments.");
  }

  //------------------------------------------------------------------------------
  IToken* FunSum::Clone() const
  {
    return new FunSum(*this);
  }

  //------------------------------------------------------------------------------
  //
  // SizeOf
  //
  //------------------------------------------------------------------------------

  FunSizeOf::FunSizeOf()
    :ICallback(cmFUNC, _T("sizeof"), 1)
  {}

  //------------------------------------------------------------------------------
  FunSizeOf::~FunSizeOf()
  {}

  //------------------------------------------------------------------------------
  /** \brief Returns the number of elements stored in the first parameter. */
  void FunSizeOf::Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc)
  {
    assert(a_iArgc==1);
    *ret = (int)(a_pArg[0]->GetArray().size());
  }

  //------------------------------------------------------------------------------
  const char_type* FunSizeOf::GetDesc() const
  {
    return _T("sizeof(a) - Returns the number of elements in a.");
  }

  //------------------------------------------------------------------------------
  IToken* FunSizeOf::Clone() const
  {
    return new FunSizeOf(*this);
  }

MUP_NAMESPACE_END
