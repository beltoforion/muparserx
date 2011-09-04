/** \file
    \brief Implementation of the interface for parser callback objects.

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
#include "mpICallback.h"
#include <cassert>

#include "mpParserBase.h"


MUP_NAMESPACE_START

  //------------------------------------------------------------------------------
  ICallback::ICallback(ECmdCode a_iCode, 
                       const char_type *a_szName, 
                       int a_nArgc,
                       const IPackage *a_pPackage)
    :IToken(a_iCode, a_szName)
    ,m_pParent(NULL)
    ,m_pPackage(a_pPackage)
    ,m_nArgc(a_nArgc)
    ,m_nArgsPresent(-1)
  {}

  //------------------------------------------------------------------------------
  ICallback::~ICallback()
  {}

  //---------------------------------------------------------------------------
  ICallback* ICallback::AsICallback()
  {
    return this;
  }

  //---------------------------------------------------------------------------
  IValue* ICallback::AsIValue()
  {
    return NULL;
  }

  //------------------------------------------------------------------------------
  bool ICallback::IsVolatile() const
  {
    return false;
  }

  //------------------------------------------------------------------------------
  /** \brief Returns a pointer to the parser object owning this callback. */
  ParserXBase* ICallback::GetParent()
  {
    assert(m_pParent);
    return m_pParent;
  }

  //------------------------------------------------------------------------------
  void  ICallback::SetArgc(int argc)
  {
    m_nArgc = argc;
  }

  //------------------------------------------------------------------------------
  /** \brief Returns the m´number of arguments required by this callback. 
      \return Number of arguments or -1 if the number of arguments is variable.  
  */
  int ICallback::GetArgc() const
  {
    return m_nArgc;
  }

  //------------------------------------------------------------------------------
  /** \brief Assign a parser object to the callback.
      \param a_pParent The parser that belongs to this callback object.

    The parent object can be used in order to access internals of the parser
    from within a callback object. Thus enabling callbacks to delete 
    variables or functions if this is desired.
  */
  void ICallback::SetParent(parent_type *a_pParent)
  {
    assert(a_pParent);
    m_pParent = a_pParent;
  }

  //------------------------------------------------------------------------------
  string_type ICallback::AsciiDump() const
  {
    stringstream_type ss;

    ss << g_sCmdCode[ GetCode() ];
    ss << _T(" [addr=0x") << std::hex << this << std::dec;
    ss << _T("; ident=\"") << GetIdent() << "\"";
    ss << _T("; argc=") << GetArgc() << " (present: " << m_nArgsPresent << ")";
    ss << _T("]");

    return ss.str();
  }

  //------------------------------------------------------------------------------
  void ICallback::SetNumArgsPresent(int argc)
  {
    m_nArgsPresent = argc;
  }

  //------------------------------------------------------------------------------
  int ICallback::GetArgsPresent() const
  {
    if (m_nArgc!=-1)
      return m_nArgc;
    else
      return m_nArgsPresent;
  }
} // namespace mu
