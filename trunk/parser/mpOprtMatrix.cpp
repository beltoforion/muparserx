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
  if (a_pArg[0]->IsArray())
  {
    array_type matrix = a_pArg[0]->GetArray();
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

MUP_NAMESPACE_END
