#ifndef MU_PACKAGE_UNIT_H
#define MU_PACKAGE_UNIT_H

#include <memory>
#include "mpIPackage.h"
#include "mpIOprt.h"

MUP_NAMESPACE_START

#define MUP_POSTFIX_DEF(CLASS)                                             \
    class CLASS : public IOprtPostfix                                      \
    {                                                                      \
    public:                                                                \
      CLASS(IPackage* pPackage=NULL);                                      \
      virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc);  \
      virtual const char_type* GetDesc() const;                            \
      virtual IToken* Clone() const;                                       \
    }; 

MUP_POSTFIX_DEF(OprtNano)
MUP_POSTFIX_DEF(OprtMicro)
MUP_POSTFIX_DEF(OprtMilli)
MUP_POSTFIX_DEF(OprtKilo)
MUP_POSTFIX_DEF(OprtMega)
MUP_POSTFIX_DEF(OprtGiga)

#undef MUP_POSTFIX_DEF

//------------------------------------------------------------------------------
/** \brief Package for installing unit postfix operators into muParserX. */
class PackageUnit : public IPackage
{
friend class std::auto_ptr<PackageUnit>;

public:
  
  static IPackage* Instance();
  virtual void AddToParser(ParserXBase *pParser);
  virtual string_type GetDesc() const;
  virtual string_type GetPrefix() const;

private:

  static std::auto_ptr<PackageUnit> s_pInstance;
};

MUP_NAMESPACE_END

#endif
