#ifndef MU_PACKAGE_NON_CMPLX_H
#define MU_PACKAGE_NON_CMPLX_H

#include <memory>
#include "mpIPackage.h"
#include "mpIOprt.h"


MUP_NAMESPACE_START

//------------------------------------------------------------------------------
/** \brief Package for installing complex functions and operators. */
class PackageNonCmplx: public IPackage
{
friend class std::auto_ptr<PackageNonCmplx>;

public:
  
  static IPackage* Instance();

  virtual void AddToParser(ParserXBase *pParser);
  virtual string_type GetDesc() const;
  virtual string_type GetPrefix() const;

private:

  static std::auto_ptr<PackageNonCmplx> s_pInstance;
};

MUP_NAMESPACE_END

#endif
