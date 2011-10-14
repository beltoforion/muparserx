/*
               __________                                 ____  ___
    _____  __ _\______   \_____ _______  ______ __________\   \/  /
   /     \|  |  \     ___/\__  \\_  __ \/  ___// __ \_  __ \     / 
  |  Y Y  \  |  /    |     / __ \|  | \/\___ \\  ___/|  | \/     \ 
  |__|_|  /____/|____|    (____  /__|  /____  >\___  >__| /___/\  \
        \/                     \/           \/     \/           \_/

  muParserX - A C++ math parser library with array and string support
  Copyright 2011 Ingo Berg

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
#ifndef MUP_FUNC_STR_H
#define MUP_FUNC_STR_H

#include "mpICallback.h"


MUP_NAMESPACE_START

  //------------------------------------------------------------------------------
  /** \brief Callback object for determining the length of a string. 
      \ingroup functions
  */
  class FunStrLen : public ICallback
  {
  public:
    FunStrLen();
    virtual void Eval(ptr_val_type& ret, const ptr_val_type *a_pArg, int a_iArgc);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  };

  //------------------------------------------------------------------------------
  /** \brief Convert a string to upper case letters. 
      \ingroup functions  
  */
  class FunStrToUpper : public ICallback
  {
  public:
    FunStrToUpper();
    virtual void Eval(ptr_val_type& ret, const ptr_val_type *a_pArg, int a_iArgc);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  };

  //------------------------------------------------------------------------------
  /** \brief Parse string to a floating point value. 
      \ingroup functions  
  */
  class FunStrToDbl : public ICallback
  {
  public:
    FunStrToDbl ();
    virtual void Eval(ptr_val_type& ret, const ptr_val_type *a_pArg, int a_iArgc);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  }; // class FunStrToDbl
}  // namespace mu

#endif
