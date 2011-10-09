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
#include "mpOprtIndex.h"
#include "mpVariable.h"

MUP_NAMESPACE_START

  //-----------------------------------------------------------------------------------------------
  //
  //  class  OprtIndex
  //
  //-----------------------------------------------------------------------------------------------

  OprtIndex::OprtIndex(IPackage* pPackage)
    :IOprtIndex(-1)
  {}

  //-----------------------------------------------------------------------------------------------
  /** \brief Index operator implementation
      \param ret A reference to the return value
      \param a_pArg Pointer to an array with the indices as ptr_val_type
      \param a_iArgc Number of indices (=dimension) actully used in the expression found. This must 
             be 1 or 2 since three dimensional data structures are not supported by muParserX.
  */
  void OprtIndex::At(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc)
  {
    try
    {
      // The index is -1, thats the actual variable reference
      if (a_iArgc!=a_pArg[-1]->GetDim())
      {
        throw ParserError(ErrorContext(ecINDEX_DIMENSION, -1, GetIdent()));
      }

      switch(a_iArgc)
      {
      case 1:
          ret.Reset(new Variable( &(ret->At(*a_pArg[0], Value(0))) ) );
          break;

      case 2:
          ret.Reset(new Variable( &(ret->At(*a_pArg[0], *a_pArg[1])) ) );
          break;

      default:
          throw ParserError(ErrorContext(ecINDEX_DIMENSION, -1, GetIdent()));
      }
    }
    catch(ParserError &exc)
    {
      exc.GetContext().Pos = GetExprPos();
      throw exc;
    }
  }

  //-----------------------------------------------------------------------------------------------
  const char_type* OprtIndex::GetDesc() const
  {
    return _T("[,] - The index operator.");
  }

  //-----------------------------------------------------------------------------------------------
  IToken* OprtIndex::Clone() const
  {
    return new OprtIndex(*this); 
  }



MUP_NAMESPACE_END
