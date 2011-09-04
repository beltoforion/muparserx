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
#ifndef MP_OPRT_NON_CMPLX_H
#define MP_OPRT_NON_CMPLX_H

/** \file 
    \brief Definitions of classes used as callbacks for standard binary operators. 
*/

/** \defgroup binop Binary operator callbacks

  This group lists the objects representing the binary operators of muParserX.
*/

#include <cmath>
#include "mpIOprt.h"
#include "mpValue.h"
#include "mpError.h"


MUP_NAMESPACE_START

  //---------------------------------------------------------------------------
  /** \brief Callback for the negative sign operator for noncomplex values.
      \ingroup infix
  */
  class OprtSign : public IOprtInfix
  {
  public:
    OprtSign();
    virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  }; // class OprtSign

  //------------------------------------------------------------------------------
  /** \brief Parser callback for implementing an addition of two noncomplex values.
      \ingroup binop
  */
  class OprtAdd : public IOprtBin    
  {
  public:
    OprtAdd();
    virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  };

  //------------------------------------------------------------------------------
  /** \brief Parser callback for implementing the subtraction of two noncomplex values.
      \ingroup binop
  */
  class OprtSub : public IOprtBin    
  {
  public:
    OprtSub();
    virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  };

  //------------------------------------------------------------------------------
  /** \brief Callback object for implementing the multiplications of noncomplex values.
      \ingroup binop
  */
  class OprtMul : public IOprtBin    
  {
  public:
    OprtMul();
    virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  };

  //------------------------------------------------------------------------------
  /** \brief Callback object for implementing the division of noncomplex values.
      \ingroup binop
  */
  class OprtDiv : public IOprtBin    
  {
  public:
    OprtDiv();
    virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  };

  //------------------------------------------------------------------------------
  /** \brief Raise x to the power of y.
      \ingroup binop
  */
  class OprtPow : public IOprtBin
  {
  public:
    
    OprtPow();
                                                                        
    virtual void Eval(ptr_val_type& ret, const ptr_val_type *arg, int argc);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  }; 
}  // namespace mu

#endif
