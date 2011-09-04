#include "mpPackageCmplx.h"

#include "mpParserBase.h"
#include "mpFuncCmplx.h"
#include "mpOprtCmplx.h"
#include "mpOprtBinCommon.h"

MUP_NAMESPACE_START

//------------------------------------------------------------------------------
std::auto_ptr<PackageCmplx> PackageCmplx::s_pInstance;

//------------------------------------------------------------------------------
IPackage* PackageCmplx::Instance()
{
  if (s_pInstance.get()==NULL)
  {
    s_pInstance.reset(new PackageCmplx);
  }

  return s_pInstance.get();
}

//------------------------------------------------------------------------------
void PackageCmplx::AddToParser(ParserXBase *pParser)
{
  // Constants
  pParser->DefineConst( _T("i"), cmplx_type(0.0, 1.0) );

  // Complex valued functions
  pParser->DefineFun(new FunCmplxReal());
  pParser->DefineFun(new FunCmplxImag());
  pParser->DefineFun(new FunCmplxConj());
  pParser->DefineFun(new FunCmplxArg());
  pParser->DefineFun(new FunCmplxNorm());
  pParser->DefineFun(new FunCmplxSin());
  pParser->DefineFun(new FunCmplxCos());
  pParser->DefineFun(new FunCmplxTan());
  pParser->DefineFun(new FunCmplxSinH());
  pParser->DefineFun(new FunCmplxCosH());
  pParser->DefineFun(new FunCmplxTanH());
  pParser->DefineFun(new FunCmplxSqrt());
  pParser->DefineFun(new FunCmplxExp());
  pParser->DefineFun(new FunCmplxLn());
  pParser->DefineFun(new FunCmplxLog());
  pParser->DefineFun(new FunCmplxLog2());
  pParser->DefineFun(new FunCmplxLog10());
  pParser->DefineFun(new FunCmplxAbs());

  // Complex valued operators
  pParser->DefineOprt(new OprtAddCmplx());
  pParser->DefineOprt(new OprtSubCmplx());
  pParser->DefineOprt(new OprtMulCmplx());
  pParser->DefineOprt(new OprtDivCmplx());
  pParser->DefineOprt(new OprtPowCmplx());
  pParser->DefineInfixOprt(new OprtSignCmplx());
}

//------------------------------------------------------------------------------
string_type PackageCmplx::GetDesc() const
{
  return _T("");
}

//------------------------------------------------------------------------------
string_type PackageCmplx::GetPrefix() const
{
  return _T("");
}

MUP_NAMESPACE_END