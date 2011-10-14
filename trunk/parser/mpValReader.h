/** \file
    \brief Definition of classes that interpret values in a string.

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
#ifndef MU_PARSER_IMPL_READER_H
#define MU_PARSER_IMPL_READER_H

#include "mpIValReader.h"



MUP_NAMESPACE_START

  //------------------------------------------------------------------------------
  //
  //  Reader for double values
  //
  //------------------------------------------------------------------------------

  /** \brief A class for reading floating point values from an expression string.
      \ingroup valreader
  */
  class DblValReader : public IValueReader
  {
  public:    
      DblValReader();
      virtual ~DblValReader();
      virtual bool IsValue(const char_type *a_szExpr, int &a_iPos, Value &a_fVal);
      virtual IValueReader* Clone(TokenReader *pTokenReader) const;
  };

  //------------------------------------------------------------------------------
  //
  //  Reader for boolean values
  //
  //------------------------------------------------------------------------------

  /** \brief A class for reading boolean values from an expression string.
      \ingroup valreader
  */
  class BoolValReader : public IValueReader
  {
  public:    
      BoolValReader();
      virtual ~BoolValReader();
      virtual bool IsValue(const char_type *a_szExpr, int &a_iPos, Value &a_fVal);
      virtual IValueReader* Clone(TokenReader *pTokenReader) const;
  };

  //------------------------------------------------------------------------------
  //
  //  Reader for hex values
  //
  //------------------------------------------------------------------------------

  /** \brief A class for reading hex values from an expression string.
      \ingroup valreader
  */
  class HexValReader : public IValueReader
  {
  public:    
      HexValReader();
      virtual bool IsValue(const char_type *a_szExpr, int &a_iPos, Value &a_fVal);
      virtual IValueReader* Clone(TokenReader *pTokenReader) const;
  };

  //------------------------------------------------------------------------------
  //
  //  Reader for binary values
  //
  //------------------------------------------------------------------------------

  /** \brief A class for reading binary values from an expression string.
      \ingroup valreader
  */
  class BinValReader : public IValueReader
  {
  public:    
      BinValReader();
      virtual ~BinValReader();
      virtual bool IsValue(const char_type *a_szExpr, int &a_iPos, Value &a_fVal);
      virtual IValueReader* Clone(TokenReader *pTokenReader) const;
  };

  //------------------------------------------------------------------------------
  //
  //  Reader for string values
  //
  //------------------------------------------------------------------------------

  /** \brief A class for reading strings from an expression string.
      \ingroup valreader
  */
  class StrValReader : public IValueReader
  {
  public:    
      StrValReader();
      virtual ~StrValReader();
      virtual bool IsValue(const char_type *a_szExpr, int &a_iPos, Value &a_fVal);
      virtual IValueReader* Clone(TokenReader *pTokenReader) const;
  };

MUP_NAMESPACE_END

#endif
