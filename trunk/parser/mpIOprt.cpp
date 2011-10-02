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
