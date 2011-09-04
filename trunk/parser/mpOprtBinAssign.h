/** \file
    \brief This file contains the definition of binary assignment 
           operators used in muParser.

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
#ifndef MUP_OPRT_BIN_ASSIGN_H
#define MUP_OPRT_BIN_ASSIGN_H

//--- Standard includes ----------------------------------------------------------
#include <cmath>

//--- muParserX framework --------------------------------------------------------
#include "mpIOprt.h"
#include "mpValue.h"
#include "mpVariable.h"
#include "mpError.h"


MUP_NAMESPACE_START

  //------------------------------------------------------------------------------
  /** \brief Assignement operator. 
  
      This operator can only be applied to variable items.
  */
  class OprtAssign : public IOprtBin
  {
  public:
    
    OprtAssign();

    virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  };

  //------------------------------------------------------------------------------
  /** \brief Assignement operator. 
    
      This operator can only be applied to variable items.
  */
  class OprtAssignAdd : public IOprtBin
  {
  public:
    OprtAssignAdd();
    virtual void Eval(ptr_val_type& ret, const ptr_val_type *a_pArg, int);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  };

  //------------------------------------------------------------------------------
  /** \brief Assignement operator. 
  
      This operator can only be applied to variable items.
  */
  class OprtAssignSub : public IOprtBin
  {
  public:
    OprtAssignSub();
    virtual void Eval(ptr_val_type& ret, const ptr_val_type *a_pArg, int);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  };

  //------------------------------------------------------------------------------
  /** \brief Assignement operator. 
  
      This operator can only be applied to variable items.
  */
  class OprtAssignMul : public IOprtBin
  {
  public:
    OprtAssignMul();
    virtual void Eval(ptr_val_type& ret, const ptr_val_type *a_pArg, int);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  };

  //------------------------------------------------------------------------------
  /** \brief Assignement operator. 
  
      This operator can only be applied to variable items.
  */
  class OprtAssignDiv : public IOprtBin
  {
  public:
    
    OprtAssignDiv();
    virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  };

MUP_NAMESPACE_END

#endif
