/** \file
    \brief Definition of basic types used by muParserX

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
#ifndef MUP_SCRIPT_TOKENS_H
#define MUP_SCRIPT_TOKENS_H

#include "mpIToken.h"


MUP_NAMESPACE_START

  //---------------------------------------------------------------------------
  /** \brief A class for encapsulation a newline token. */
  class TokenNewline : public IToken
  {
  public:

      TokenNewline();

      //---------------------------------------------
      // IToken interface
      //---------------------------------------------

      virtual IToken* Clone() const;
      virtual string_type AsciiDump() const;

      int GetStackOffset() const;
      void SetStackOffset(int nOffset);

  private:
      int m_nOffset;
  };

MUP_NAMESPACE_END

#endif