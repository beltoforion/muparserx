#include "mpPackageNonCmplx.h"

#include "mpParserBase.h"
#include "mpFuncNonCmplx.h"
#include "mpOprtNonCmplx.h"
#include "mpOprtBinCommon.h"


MUP_NAMESPACE_START

//------------------------------------------------------------------------------
std::auto_ptr<PackageNonCmplx> PackageNonCmplx::s_pInstance;

//------------------------------------------------------------------------------
IPackage* PackageNonCmplx::Instance()
{
  if (s_pInstance.get()==NULL)
  {
    s_pInstance.reset(new PackageNonCmplx);
  }

  return s_pInstance.get();
}

//------------------------------------------------------------------------------
void PackageNonCmplx::AddToParser(ParserXBase *pParser)
{
  pParser->DefineFun(new FunSin());
  pParser->DefineFun(new FunCos());
  pParser->DefineFun(new FunTan());
  pParser->DefineFun(new FunSinH());
  pParser->DefineFun(new FunCosH());
  pParser->DefineFun(new FunTanH());
  pParser->DefineFun(new FunASin());
  pParser->DefineFun(new FunACos());
  pParser->DefineFun(new FunATan());
  pParser->DefineFun(new FunASinH());
  pParser->DefineFun(new FunACosH());
  pParser->DefineFun(new FunATanH());
  pParser->DefineFun(new FunLog());
  pParser->DefineFun(new FunLog10());
  pParser->DefineFun(new FunLog2());
  pParser->DefineFun(new FunLn());
  pParser->DefineFun(new FunExp());
  pParser->DefineFun(new FunSqrt());
  pParser->DefineFun(new FunAbs());

  // Operator callbacks
  pParser->DefineInfixOprt(new OprtSign());
  pParser->DefineOprt(new OprtAdd());
  pParser->DefineOprt(new OprtSub());
  pParser->DefineOprt(new OprtMul());
  pParser->DefineOprt(new OprtDiv());
  pParser->DefineOprt(new OprtPow);
}

//------------------------------------------------------------------------------
string_type PackageNonCmplx::GetDesc() const
{
  return _T("");
}

//------------------------------------------------------------------------------
string_type PackageNonCmplx::GetPrefix() const
{
  return _T("");
}

MUP_NAMESPACE_END