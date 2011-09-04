/** \file
    \brief Definition of the token reader used to break the expression string up 
           into tokens.

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

#ifndef MUP_TOKEN_READER_H
#define MUP_TOKEN_READER_H

//--- Standard includes ----------------------------------------------------
#include <cstdio>
#include <cstring>
#include <map>
#include <stack>
#include <string>
#include <list>

//--- muParserX framework --------------------------------------------------
#include "mpIToken.h"
#include "mpError.h"
#include "mpStack.h"
#include "mpFwdDecl.h"

MUP_NAMESPACE_START

  /** \brief Token reader for the ParserXBase class. */
  class TokenReader
  {
  friend class ParserXBase;

  public:

    typedef std::vector<ptr_tok_type> token_buf_type;

  private:

    TokenReader(const TokenReader &a_Reader);
    TokenReader& operator=(const TokenReader &a_Reader);
    void Assign(const TokenReader &a_Reader);
    void DeleteValReader();
    void SetParent(ParserXBase *a_pParent);

    int ExtractToken(const char_type *a_szCharSet, string_type &a_sTok, int a_iPos) const;

    bool IsBuiltIn(ptr_tok_type &t);
    bool IsEOF(ptr_tok_type &t);
    bool IsNewline(ptr_tok_type &a_Tok);
    bool IsNewLine(ptr_tok_type &t);
    bool IsInfixOpTok(ptr_tok_type &t);
    bool IsFunTok(ptr_tok_type &t);
    bool IsPostOpTok(ptr_tok_type &t);
    bool IsOprt(ptr_tok_type &t);
    bool IsValTok(ptr_tok_type &t);
    bool IsVarOrConstTok(ptr_tok_type &t);
    bool IsUndefVarTok(ptr_tok_type &t);
    bool IsComment();

    const ptr_tok_type& Store(const ptr_tok_type &t, int pos);

    ParserXBase *m_pParser;  ///< Pointer to the parser bound to this token reader
    string_type m_sExpr;     ///< The expression beeing currently parsed
    int  m_nPos;             ///< Current parsing position in the expression
    int  m_nNumBra;          ///< Number of open parenthesis
    int  m_nNumIndex;        ///< Number of open index paranethesis    
    int  m_nNumIfElse;       ///< Coubter for if-then-else levels
    int  m_nSynFlags;        ///< Flags to controll the syntax flow

    token_buf_type m_vTokens;
    ECmdCode m_eLastTokCode;

    mutable fun_maptype  *m_pFunDef;
    mutable oprt_bin_multimap *m_pOprtDef;
    mutable oprt_ifx_maptype *m_pInfixOprtDef;
    mutable oprt_pfx_maptype *m_pPostOprtDef;
    mutable val_maptype  *m_pConstDef;
    val_vec_type *m_pDynVarShadowValues; ///< Value items created for holding values of variables created at parser runtime
    var_maptype  *m_pVarDef;             ///< The only non const pointer to parser internals

    readervec_type m_vValueReader;  ///< Value token identification function
    var_maptype m_UsedVar;
    float_type m_fZero;             ///< Dummy value of zero, referenced by undefined variables

  public:

    TokenReader(ParserXBase *a_pParent);
   ~TokenReader();
    TokenReader* Clone(ParserXBase *a_pParent) const;
    
    void AddValueReader(IValueReader *a_pReader);
    void AddSynFlags(int flag);
    //void SetVarCreator(facfun_type a_pFactory);
    int GetPos() const;
    const string_type& GetExpr() const;
    const var_maptype& GetUsedVar() const;
    const token_buf_type& GetTokens() const;
    void SetExpr(const string_type &a_sExpr);

    void ReInit();
    ptr_tok_type ReadNextToken();
  }; // class TokenReader

MUP_NAMESPACE_END

#endif


