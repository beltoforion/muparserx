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
#ifndef MUP_COMPLEX_FUNCTIONS_H
#define MUP_COMPLEX_FUNCTIONS_H

#include "mpICallback.h"


MUP_NAMESPACE_START

  //-----------------------------------------------------------------------
  /** \brief Parser callback object for returning the real part of a complex number.
      \ingroup functions
  */
  class FunCmplxReal : public ICallback
  {
  public:
    FunCmplxReal(IPackage *pPackage = NULL);
    virtual ~FunCmplxReal();
    virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  };

  //-----------------------------------------------------------------------
  /** \brief Parser callback object for returning the imaginary part of a complex number.
      \ingroup functions
  */
  class FunCmplxImag : public ICallback
  {
  public:
    FunCmplxImag();
    virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  };

  //-----------------------------------------------------------------------
  /** \brief Parser callback object for returning the complex conjugate of 
             the complex number.
      \ingroup functions
  */
  class FunCmplxConj : public ICallback
  {
  public:
    FunCmplxConj();
    virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  };


  //-----------------------------------------------------------------------
  /** \brief Parser callback object for returning the phase angle 
             (or angular component) of a complex number, expressed in radians.
      \ingroup functions
  */
  class FunCmplxArg : public ICallback
  {
  public:
    FunCmplxArg();
    virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  };

  //-----------------------------------------------------------------------
  /** \brief Parser callback object for returning the norm value of the 
             complex number phase angle.
      \ingroup functions
  */
  class FunCmplxNorm : public ICallback
  {
  public:
    FunCmplxNorm();
    virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  };

  //-----------------------------------------------------------------------
  class FunCmplxCos : public ICallback
  {
  public:
    FunCmplxCos();
    virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  };

  //-----------------------------------------------------------------------
  class FunCmplxSin : public ICallback
  {
  public:
    FunCmplxSin();
    virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  };

  //-----------------------------------------------------------------------
  class FunCmplxCosH : public ICallback
  {
  public:
    FunCmplxCosH();
    virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  };

  //-----------------------------------------------------------------------
  class FunCmplxSinH : public ICallback
  {
  public:
    FunCmplxSinH();
    virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  };

  //-----------------------------------------------------------------------
  class FunCmplxTan : public ICallback
  {
  public:
    FunCmplxTan();
    virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  };

  //-----------------------------------------------------------------------
  class FunCmplxTanH : public ICallback
  {
  public:
    FunCmplxTanH();
    virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  };

  //-----------------------------------------------------------------------
  class FunCmplxSqrt : public ICallback
  {
  public:
    FunCmplxSqrt();
    virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  };

  //-----------------------------------------------------------------------
  class FunCmplxExp : public ICallback
  {
  public:
    FunCmplxExp();
    virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  };

  //-----------------------------------------------------------------------
  class FunCmplxLn : public ICallback
  {
  public:
    FunCmplxLn();
    virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  };

  //-----------------------------------------------------------------------
  class FunCmplxLog : public ICallback
  {
  public:
    FunCmplxLog();
    virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  };

  //-----------------------------------------------------------------------
  class FunCmplxLog10 : public ICallback
  {
  public:
    FunCmplxLog10();
    virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  };

  //-----------------------------------------------------------------------
  class FunCmplxLog2 : public ICallback
  {
  public:
    FunCmplxLog2();
    virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  };

  //-----------------------------------------------------------------------
  class FunCmplxAbs : public ICallback
  {
  public:

    FunCmplxAbs();
    virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  };
}  // namespace mu

#endif
