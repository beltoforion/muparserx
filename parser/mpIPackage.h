#ifndef MU_IPACKAGE_H
#define MU_IPACKAGE_H

#include <vector>
#include "mpFwdDecl.h"
#include "mpTypes.h"


MUP_NAMESPACE_START

class IPackage
{
public:

  virtual void AddToParser(ParserXBase *pParser) = 0;
  virtual string_type GetDesc() const = 0;
  virtual string_type GetPrefix() const = 0;

protected:

  IPackage();
  virtual ~IPackage();
};

MUP_NAMESPACE_END

#endif