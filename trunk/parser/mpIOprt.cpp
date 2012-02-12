/*
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
*/
#include "mpIOprt.h"

#include "mpError.h"


MUP_NAMESPACE_START

  //------------------------------------------------------------------------------
  //
  // Binary Operators
  //
  //------------------------------------------------------------------------------

  IOprtBin::IOprtBin(const char_type *a_szIdent, int nPrec, EOprtAsct eAsc)
    :ICallback(cmOPRT_BIN, a_szIdent, 2)
    ,IPrecedence()
    ,m_nPrec(nPrec)
    ,m_eAsc(eAsc)
  {}

  //------------------------------------------------------------------------------
  IOprtBin::~IOprtBin()
  {}

  //------------------------------------------------------------------------------
  string_type IOprtBin::AsciiDump() const
  {
    stringstream_type ss;

    ss << g_sCmdCode[ GetCode() ];
    ss << _T(" [addr=0x") << std::hex << this << std::dec;
    ss << _T("; ident=\"") << GetIdent() << _T("\"");
    ss << _T("; prec=") << GetPri();
    ss << _T("; argc=") << GetArgc();
    ss << _T("]");

    return ss.str();
  }

  //------------------------------------------------------------------------------
  int IOprtBin::GetPri() const
  {
    return m_nPrec;
  }

  //------------------------------------------------------------------------------
  EOprtAsct IOprtBin::GetAssociativity() const
  {
    return m_eAsc;
  }

  //------------------------------------------------------------------------------
  /** \brief Verify the operator prototype.

    Binary operators have the additional constraint that return type and the types
    of both arguments must be the same. So adding to floats can not produce a string
    and adding a number to a string is impossible.
  */
  void IOprtBin::CheckPrototype(const string_type &a_sProt)
  {
    if (a_sProt.length()!=4)
      throw ParserError( ErrorContext(ecAPI_INVALID_PROTOTYPE, -1, GetIdent() ) ); 

    //if (a_sProt[0]!=a_sProt[2] || a_sProt[0]!=a_sProt[3])
    //  throw ParserError( ErrorContext(ecAPI_INVALID_PROTOTYPE, -1, GetIdent() ) ); 
  }

  //---------------------------------------------------------------------------
  IPrecedence* IOprtBin::AsIPrecedence()
  {
    return this;
  }

  //------------------------------------------------------------------------------
  //
  // Unary Postfix Operators
  //
  //------------------------------------------------------------------------------

  IOprtPostfix::IOprtPostfix(const char_type *a_szIdent)
    :ICallback(cmOPRT_POSTFIX, a_szIdent, 1)
  {}

  //------------------------------------------------------------------------------
  IOprtPostfix::~IOprtPostfix()
  {}

  //------------------------------------------------------------------------------
  string_type IOprtPostfix::AsciiDump() const
  {
    stringstream_type ss;

    ss << g_sCmdCode[ GetCode() ];
    ss << _T(" [addr=0x") << std::hex << this << std::dec;
    ss << _T("; ident=\"") << GetIdent() << _T("\"");
    ss << _T("; argc=") << GetArgc();
    ss << _T("]");

    return ss.str();
  }

  //------------------------------------------------------------------------------
  //
  // Unary Infix Operators
  //
  //------------------------------------------------------------------------------

  IOprtInfix::IOprtInfix(const char_type *a_szIdent)
    :ICallback(cmOPRT_INFIX, a_szIdent, 1)
  {}

  //------------------------------------------------------------------------------
  IOprtInfix::~IOprtInfix()
  {}

  //------------------------------------------------------------------------------
  string_type IOprtInfix::AsciiDump() const
  {
    stringstream_type ss;

    ss << g_sCmdCode[ GetCode() ];
    ss << _T(" [addr=0x") << std::hex << this << std::dec;
    ss << _T("; ident=\"") << GetIdent() << _T("\"");
    ss << _T("; argc=") << GetArgc();
    ss << _T("]");

    return ss.str();
  }

  //------------------------------------------------------------------------------
  //
  // Index operators
  //
  //------------------------------------------------------------------------------

  IOprtIndex::IOprtIndex(int nArgc)
    :IToken(cmIC, _T("[...]"))
    ,m_nArgc(nArgc)
  {}

  //------------------------------------------------------------------------------
  IOprtIndex::~IOprtIndex()
  {}

  //------------------------------------------------------------------------------
  string_type IOprtIndex::AsciiDump() const
  {
    stringstream_type ss;

    ss << g_sCmdCode[ GetCode() ];
    ss << _T(" [addr=0x") << std::hex << this << std::dec;
    ss << _T("; ident=\"") << GetIdent() << _T("\"");
    ss << _T("; argc=") << GetArgc();
    ss << _T("]");

    return ss.str();
  }

  //-----------------------------------------------------------------------------------------------
  IOprtIndex* IOprtIndex::AsIOprtIndex()
  {
    return this;
  }

  //-----------------------------------------------------------------------------------------------
  int  IOprtIndex::GetArgc() const
  {
    return m_nArgc;
  }

  //-----------------------------------------------------------------------------------------------
  void IOprtIndex::SetNumArgsPresent(int argc)
  {
    m_nArgsPresent = argc;
  }

  //-----------------------------------------------------------------------------------------------
  int IOprtIndex::GetArgsPresent() const
  {
    if (m_nArgc!=-1)
      return m_nArgc;
    else
      return m_nArgsPresent;
  }
}  // namespace mu
