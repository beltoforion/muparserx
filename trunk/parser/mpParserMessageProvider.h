#ifndef MP_PARSER_MESSAGE_PROVIDER_H
#define MP_PARSER_MESSAGE_PROVIDER_H

#include <vector>
#include <memory>

#include "mpDefines.h"
#include "mpTypes.h"


MUP_NAMESPACE_START

  //-----------------------------------------------------------------------------------------------
  /** \brief Base class for Parser Message providing classes. */
  class ParserMessageProviderBase
  {
  public:

    ParserMessageProviderBase();
    virtual ~ParserMessageProviderBase();

    string_type operator[](unsigned a_iIdx) const;

  private:
    // Disable CC and assignment operator for this class and derivatives
    ParserMessageProviderBase(const ParserMessageProviderBase &ref);
    ParserMessageProviderBase& operator=(const ParserMessageProviderBase &ref);

  protected:
    std::vector<string_type>  m_vErrMsg;
  };

  //-----------------------------------------------------------------------------------------------
  class ParserMessageProviderEnglish : public ParserMessageProviderBase
  {
  friend class std::auto_ptr<ParserMessageProviderEnglish>;

  public:
    ParserMessageProviderEnglish();
  };

  //-----------------------------------------------------------------------------------------------
  class ParserMessageProviderGerman : public ParserMessageProviderBase
  {
  friend class std::auto_ptr<ParserMessageProviderGerman>;

  public:
    ParserMessageProviderGerman();
  };

MUP_NAMESPACE_END

#endif