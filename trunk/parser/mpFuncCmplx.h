/** \file
    \brief Definition of functions for complex valued operations.

<pre>
               __________                                 ____  ___
    _____  __ _\______   \_____ _______  ______ __________\   \/  /
   /     \|  |  \     ___/\__  \\_  __ \/  ___// __ \_  __ \     / 
  |  Y Y  \  |  /    |     / __ \|  | \/\___ \\  ___/|  | \/     \ 
  |__|_|  /____/|____|    (____  /__|  /____  >\___  >__| /___/\  \
        \/                     \/           \/     \/           \_/
                                       Copyright (C) 2012 Ingo Berg
                                       All rights reserved.

  muParserX - A C++ math parser library with array and string support
  Copyright (c) 2012, Ingo Berg
  All rights reserved.

  Redistribution and use in source and binary forms, with or without 
  modification, are permitted provided that the following conditions are met:

   * Redistributions of source code must retain the above copyright notice, 
     this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright notice, 
     this list of conditions and the following disclaimer in the documentation 
     and/or other materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
  POSSIBILITY OF SUCH DAMAGE.
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
