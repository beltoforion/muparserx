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
#ifndef MUP_FUNC_COMMON_H
#define MUP_FUNC_COMMON_H

#include "mpICallback.h"


MUP_NAMESPACE_START

  //------------------------------------------------------------------------------
  /** \brief Parser function callback for determining the size of an array. 
      \ingroup functions
  */
  class FunParserID : public ICallback
  {
  public:
    FunParserID ();
    virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  }; // class FunParserID

  //------------------------------------------------------------------------------
  /** \brief Determine maximal value from the parameter list. 
      \ingroup functions
  */
  class FunMax : public ICallback
  {
  public:
    FunMax();
    virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  }; // class FunMax

  //------------------------------------------------------------------------------
  /** \brief Determine minimal value from the parameter list. 
      \ingroup functions
  */
  class FunMin : public ICallback
  {
  public:
    FunMin();
    virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  }; // class FunMin

  //------------------------------------------------------------------------------
  /** \brief Parser callback for summing up all function arguments. 
      \ingroup functions
  */  
  class FunSum : public ICallback
  {
  public:
    FunSum();
    virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  }; // class FunSum

  //------------------------------------------------------------------------------
  /** \brief Parser function callback for determining the size of an array. 
      \ingroup functions
  */
  class FunSizeOf : public ICallback
  {
  public:
    FunSizeOf();
    virtual ~FunSizeOf();
    virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  }; // class FunSizeOf

MUP_NAMESPACE_END

#endif
