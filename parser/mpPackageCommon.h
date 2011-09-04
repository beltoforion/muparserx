#ifndef MU_PACKAGE_COMMON_H
#define MU_PACKAGE_COMMON_H

#include <memory>
#include "mpIPackage.h"
#include "mpIOprt.h"


MUP_NAMESPACE_START

//------------------------------------------------------------------------------
/** \brief Package for installing operators and functions which
           are always present. 
*/
class PackageCommon: public IPackage
{
friend class std::auto_ptr<PackageCommon>;

public:
  
  static IPackage* Instance();
  virtual void AddToParser(ParserXBase *pParser);
  virtual string_type GetDesc() const;
  virtual string_type GetPrefix() const;

private:

  static std::auto_ptr<PackageCommon> s_pInstance;
};

MUP_NAMESPACE_END

#endif
