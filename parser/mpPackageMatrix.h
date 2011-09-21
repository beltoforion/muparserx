#ifndef MU_PACKAGE_MATRIX_H
#define MU_PACKAGE_MATRIX_H

#include <memory>
#include "mpIPackage.h"
#include "mpIOprt.h"


MUP_NAMESPACE_START

//------------------------------------------------------------------------------
/** \brief Package for installing complex functions and operators. */
class PackageMatrix : public IPackage
{
friend class std::auto_ptr<PackageMatrix>;

public:
  
  static IPackage* Instance();
  virtual void AddToParser(ParserXBase *pParser);
  virtual string_type GetDesc() const;
  virtual string_type GetPrefix() const;

private:

  static std::auto_ptr<PackageMatrix> s_pInstance;
};

MUP_NAMESPACE_END

#endif
