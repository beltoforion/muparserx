#include "mpScriptTokens.h"
#include "mpTypes.h"


MUP_NAMESPACE_START

  //---------------------------------------------------------------------------
  TokenNewline::TokenNewline()
    :IToken(cmSCRIPT_NEWLINE)
    ,m_nOffset(0)
  {}

  //---------------------------------------------------------------------------
  IToken* TokenNewline::Clone() const
  {
    return new TokenNewline(*this);
  }

  //---------------------------------------------------------------------------
  void TokenNewline::SetStackOffset(int nOffset)
  {
    m_nOffset = nOffset;
  }

  //---------------------------------------------------------------------------
  int TokenNewline::GetStackOffset() const
  {
    return m_nOffset;
  }

  //---------------------------------------------------------------------------
  string_type TokenNewline::AsciiDump() const
  {
    stringstream_type ss;

    ss << "NEWLINE";
    ss << _T(" [addr=0x") << std::hex << this << std::dec;
    ss << _T(" ; offset=") << m_nOffset;
    ss << _T("]");
    return ss.str();
  }
  
MUP_NAMESPACE_END