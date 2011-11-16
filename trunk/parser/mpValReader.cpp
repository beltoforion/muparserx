/** \file
    \brief Implementation of classes that interpret values in a string.

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
#include "mpValReader.h"
#include "mpError.h"


MUP_NAMESPACE_START

  //------------------------------------------------------------------------------
  //
  //  Reader for floating point values
  //
  //------------------------------------------------------------------------------

  DblValReader::DblValReader()
    :IValueReader()
  {}

  //------------------------------------------------------------------------------
  DblValReader::~DblValReader()
  {}

  //------------------------------------------------------------------------------
  bool DblValReader::IsValue(const char_type *a_szExpr, int &a_iPos, Value &a_Val)
  {
    stringstream_type stream(a_szExpr + a_iPos);
    float_type fVal(0);
    std::streamoff iStart(0), iEnd(0);

    iStart = stream.tellg(); // Record position before reading
    stream >> fVal;

	// todo: check against GCC 4.6 implement using stream.fail(), remove space
	//		 that is always inserted at the end of an expression
	// if(stream.fail())
    //   return false;

    iEnd = stream.tellg();   // Position after reading

    if (iEnd==-1)
      return false;

    a_iPos += (int)iEnd;
    
    // Finally i have to check if the next sign is the "i" for a imaginary unit
    // if so this is an imaginary value
    if (a_szExpr[a_iPos]=='i')
    {
      a_Val = cmplx_type(0.0, fVal);
      a_iPos++;
    }
    else
    {
      a_Val = cmplx_type(fVal, 0.0);
    }

    return true;
  }

  //------------------------------------------------------------------------------
  IValueReader* DblValReader::Clone(TokenReader *pTokenReader) const
  {
    IValueReader *pReader = new DblValReader(*this);
    pReader->SetParent(pTokenReader);

    return pReader;
  }

  //------------------------------------------------------------------------------
  //
  //  Reader for boolean values
  //
  //------------------------------------------------------------------------------

  BoolValReader::BoolValReader()
    :IValueReader()
  {}

  //------------------------------------------------------------------------------
  BoolValReader::~BoolValReader()
  {}

  //------------------------------------------------------------------------------
  bool BoolValReader::IsValue(const char_type *a_szExpr, int &a_iPos, Value &a_Val)
  {
    string_type sExpr(a_szExpr + a_iPos);

    if (sExpr.find(_T("true"))==0)
    {
      a_Val = true;
      a_iPos += 4;
      return true;
    }
    else if (sExpr.find(_T("false"))==0)
    {
      a_Val = false;
      a_iPos += 5;
      return true;
    }

    return false;
  }

  //------------------------------------------------------------------------------
  IValueReader* BoolValReader::Clone(TokenReader *pTokenReader) const
  {
    IValueReader *pReader = new BoolValReader(*this);
    pReader->SetParent(pTokenReader);

    return pReader;
  }

  //------------------------------------------------------------------------------
  //
  //  Reader for hex values
  //
  //------------------------------------------------------------------------------

  HexValReader::HexValReader()
    :IValueReader()
  {}

  //------------------------------------------------------------------------------
  /** \brief Try to read a hex value from a given position in the expression. 
      \param a_szExpr The Expression
      \param [in/out] a_iPos The current position in the expression
      \param [out] a_val The value that was read

    Hex values must start with a "0x" characters. The position a_iPos is advanded in case 
    a hex value was found.
  */
  bool HexValReader::IsValue(const char_type *a_szExpr, int &a_iPos, Value &a_val)
  {
		std::size_t len = std::char_traits<char_type>::length(a_szExpr);
    if ( a_iPos>=(int)len || a_szExpr[a_iPos+1]!='x' || a_szExpr[a_iPos+1]==0 || a_szExpr[a_iPos]!='0') 
      return 0;

    unsigned iVal(0);

    stringstream_type::pos_type nPos(0);
    stringstream_type ss(a_szExpr + a_iPos + 2);
    ss >> std::hex >> iVal;
    nPos = ss.tellg();

    if (nPos==(stringstream_type::pos_type)0)
      return 1;

    a_iPos += (int)(2 + nPos);
    a_val = (int)iVal;
    return 1;
  }

  //------------------------------------------------------------------------------
  IValueReader* HexValReader::Clone(TokenReader *pTokenReader) const
  {
    IValueReader *pReader = new HexValReader(*this);
    pReader->SetParent(pTokenReader);
    return pReader;
  }

  //------------------------------------------------------------------------------
  //
  //  Reader for binary values
  //
  //------------------------------------------------------------------------------

  BinValReader::BinValReader()
    :IValueReader()
  {}

  //------------------------------------------------------------------------------
  BinValReader::~BinValReader()
  {}

  //------------------------------------------------------------------------------
  bool BinValReader::IsValue(const char_type *a_szExpr, int &a_iPos, Value &a_Val)
  {
    const char_type *szExpr = a_szExpr + a_iPos;

    if (szExpr[0]!='#') 
      return false;

    unsigned iVal = 0, iBits = sizeof(iVal)*8, i;
    for (i=0; (szExpr[i+1]=='0' || szExpr[i+1]=='1') && i<iBits; ++i)
      iVal |= (int)(szExpr[i+1]=='1') << ((iBits-1)-i);

    if (i==0) 
      return false;

    if (i==iBits)
      throw ParserError(_T("Binary to integer conversion error (overflow)."));

    a_Val = (int)(iVal >> (iBits-i) );
    a_iPos += i+1;

    return true;
  }

  //------------------------------------------------------------------------------
  IValueReader* BinValReader::Clone(TokenReader *pTokenReader) const
  {
    IValueReader *pReader = new BinValReader(*this);
    pReader->SetParent(pTokenReader);

    return pReader;
  }

  //------------------------------------------------------------------------------
  //
  //  Reader for string values
  //
  //------------------------------------------------------------------------------

  StrValReader::StrValReader()
    :IValueReader()
  {}

  //------------------------------------------------------------------------------
  StrValReader::~StrValReader()
  {}

  //------------------------------------------------------------------------------
  bool StrValReader::IsValue(const char_type *a_pszExpr, int &a_iPos, Value &a_Val)
  {
    const char_type *szExpr = a_pszExpr + a_iPos;

    
    if (szExpr[0]!='"') 
      return false;

    string_type sBuf(&szExpr[1]);
    std::size_t iEnd(0), iSkip(0);

    // parser over escaped '\"' end replace them with '"'
    for(iEnd=sBuf.find(_T("\"")); iEnd!=string_type::npos; iEnd=sBuf.find(_T("\""), iEnd))
    {
      if (sBuf[iEnd-1]!='\\') break;
      sBuf.replace(iEnd-1, 2, _T("\""));
      iSkip++;
    }

    if (iEnd==string_type::npos)
      throw ParserError( ErrorContext(ecUNTERMINATED_STRING, a_iPos) );

    string_type sTok(sBuf.begin(), sBuf.begin()+iEnd);
    a_Val = sTok;
    a_iPos += (int)(sTok.length() + 2 + iSkip);  // +2 wg Anführungszeichen; +iSkip für entfernte escape zeichen
    return true;
  }

  //------------------------------------------------------------------------------
  IValueReader* StrValReader::Clone(TokenReader *pTokenReader) const
  {
    IValueReader *pReader = new StrValReader(*this);
    pReader->SetParent(pTokenReader);

    return pReader;
  }
} // namespace mu
