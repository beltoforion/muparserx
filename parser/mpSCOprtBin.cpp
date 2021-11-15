/*
               __________                                 ____  ___
    _____  __ _\______   \_____ _______  ______ __________\   \/  /
   /     \|  |  \     ___/\__  \\_  __ \/  ___// __ \_  __ \     / 
  |  Y Y  \  |  /    |     / __ \|  | \/\___ \\  ___/|  | \/     \ 
  |__|_|  /____/|____|    (____  /__|  /____  >\___  >__| /___/\  \
        \/                     \/           \/     \/           \_/
                                       Copyright (C) 2016, Ingo Berg
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
*/
#include "mpSCOprtBin.h"

MUP_NAMESPACE_START
//-----------------------------------------------------------------------------------------------
//
// class SCOprtLOrBegin
//
//-----------------------------------------------------------------------------------------------

SCOprtLOrBegin::SCOprtLOrBegin(const char_type *szIdent)
    :ISCOprtBin(cmSCBEGIN, szIdent, (int)prLOGIC_OR, oaLEFT)
{}


//-----------------------------------------------------------------------------------------------
IToken* SCOprtLOrBegin::Clone() const
{
    return new SCOprtLOrBegin(*this);
}


//-----------------------------------------------------------------------------------------------
//
// class SCOprtLOrEnd
//
//-----------------------------------------------------------------------------------------------

SCOprtLOrEnd::SCOprtLOrEnd(const char_type *szIdent)
    :ISCOprtBin(cmSCEND, szIdent, (int)prLOGIC_OR, oaLEFT)
{}


//-----------------------------------------------------------------------------------------------
IToken* SCOprtLOrEnd::Clone() const
{
    return new SCOprtLOrEnd(*this);
}

//-----------------------------------------------------------------------------------------------
//
// class SCOprtLAndBegin
//
//-----------------------------------------------------------------------------------------------

SCOprtLAndBegin::SCOprtLAndBegin(const char_type *szIdent)
    :ISCOprtBin(cmSCBEGIN, szIdent, (int)prLOGIC_AND, oaLEFT)
{}

//-----------------------------------------------------------------------------------------------
IToken* SCOprtLAndBegin::Clone() const
{
    return new SCOprtLAndBegin(*this);
}


//-----------------------------------------------------------------------------------------------
//
// class SCOprtLAndBegin
//
//-----------------------------------------------------------------------------------------------

SCOprtLAndEnd::SCOprtLAndEnd(const char_type *szIdent)
    :ISCOprtBin(cmSCEND, szIdent, (int)prLOGIC_AND, oaLEFT)
{}

//-----------------------------------------------------------------------------------------------
IToken* SCOprtLAndEnd::Clone() const
{
    return new SCOprtLAndEnd(*this);
}

}