/** \file
    \brief Definition of the parser class

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
#ifndef MUP_PARSERX_H
#define MUP_PARSERX_H

//--- Parser framework -----------------------------------------------------
#include "mpDefines.h"
#include "mpParserBase.h"


MUP_NAMESPACE_START

/** \brief The parser implementation.
      \sa ParserXBase

    This is the class that implements the parser. It installs all functions
    and operatore and defines the constants.
  */
  class ParserX : public ParserXBase
  {
  public:
    ParserX(EPackages ePackages = pckALL_COMPLEX);
  };
} // namespace mu

#endif

