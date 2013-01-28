/** \file
    \brief Definition of functions for complex valued operations.

<pre>
               __________                                 ____  ___
    _____  __ _\______   \_____ _______  ______ __________\   \/  /
   /     \|  |  \     ___/\__  \\_  __ \/  ___// __ \_  __ \     / 
  |  Y Y  \  |  /    |     / __ \|  | \/\___ \\  ___/|  | \/     \ 
  |__|_|  /____/|____|    (____  /__|  /____  >\___  >__| /___/\  \
        \/                     \/           \/     \/           \_/
                                       Copyright (C) 2013 Ingo Berg
                                       All rights reserved.

  muParserX - A C++ math parser library with array and string support
  Copyright (c) 2013, Ingo Berg
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
#ifndef MUP_FUNC_MATRIX_H
#define MUP_FUNC_MATRIX_H

#include "mpICallback.h"


MUP_NAMESPACE_START

  //-----------------------------------------------------------------------
  /** \brief Parser callback object for creating matrices consisting 
             entirely of ones.
      \ingroup functions
  */
  class FunMatrixOnes : public ICallback
  {
  public:
    FunMatrixOnes(IPackage *pPackage = NULL);
    virtual ~FunMatrixOnes();
    virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  };

  //-----------------------------------------------------------------------
  /** \brief Parser callback object for creating matrices consisting 
             entirely of zeros.
      \ingroup functions
  */
  class FunMatrixZeros : public ICallback
  {
  public:
    FunMatrixZeros(IPackage *pPackage = NULL);
    virtual ~FunMatrixZeros();
    virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  };

  //-----------------------------------------------------------------------
  /** \brief Parser callback object for creating unity matrices.
      \ingroup functions
  */
  class FunMatrixEye : public ICallback
  {
  public:
    FunMatrixEye(IPackage *pPackage = NULL);
    virtual ~FunMatrixEye();
    virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  };


  //-----------------------------------------------------------------------
  /** \brief Determines the dimensions of a matrix.
      \ingroup functions
  */
  class FunMatrixSize : public ICallback
  {
  public:
    FunMatrixSize(IPackage *pPackage = NULL);
    virtual ~FunMatrixSize();
    virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc);
    virtual const char_type* GetDesc() const;
    virtual IToken* Clone() const;
  };
}  // namespace mu

#endif