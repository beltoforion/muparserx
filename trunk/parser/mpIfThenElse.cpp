#include "mpIfThenElse.h"

MUP_NAMESPACE_START

  //---------------------------------------------------------------------------
  //
  // If part of if-then-else clauses
  //
  //---------------------------------------------------------------------------

  TokenIfThenElse::TokenIfThenElse(ECmdCode eCode)
    :IToken(eCode, g_sCmdCode[ eCode ])
    ,IPrecedence()
    ,m_nOffset()
  {}

  //---------------------------------------------------------------------------
  IToken* TokenIfThenElse::Clone() const
  {
    return new TokenIfThenElse(*this);
  }

  //---------------------------------------------------------------------------
  void TokenIfThenElse::SetOffset(int nOffset)
  {
    m_nOffset = nOffset;
  }

  //---------------------------------------------------------------------------
  int TokenIfThenElse::GetOffset() const
  {
    return m_nOffset;
  }

  //---------------------------------------------------------------------------
  string_type TokenIfThenElse::AsciiDump() const
  {
    stringstream_type ss;

    ss << GetIdent();
    ss << _T(" [addr=0x") << std::hex << this << std::dec;
    ss << _T("; offset=") << m_nOffset;
    ss << _T("]");
    return ss.str();
  }
  
  //---------------------------------------------------------------------------
  int TokenIfThenElse::GetPri() const
  {
    return (int)prIF_THEN_ELSE;
  }

  //---------------------------------------------------------------------------
  EOprtAsct TokenIfThenElse::GetAssociativity() const
  {
    return oaNONE;
  }

  //---------------------------------------------------------------------------
  IPrecedence* TokenIfThenElse::AsIPrecedence()
  {
    return this;
  }

MUP_NAMESPACE_END