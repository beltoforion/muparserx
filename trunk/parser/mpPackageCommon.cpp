#include "mpPackageCommon.h"

#include "mpParserBase.h"
#include "mpFuncNonCmplx.h"
#include "mpFuncCommon.h"
#include "mpOprtBinCommon.h"
#include "mpOprtBinAssign.h"
#include "mpValReader.h"

/** \brief Pi (what else?). */
#define MUP_CONST_PI  3.141592653589793238462643

/** \brief The eulerian number. */
#define MUP_CONST_E   2.718281828459045235360287


MUP_NAMESPACE_START

//------------------------------------------------------------------------------
std::auto_ptr<PackageCommon> PackageCommon::s_pInstance;

//------------------------------------------------------------------------------
IPackage* PackageCommon::Instance()
{
  if (s_pInstance.get()==NULL)
  {
    s_pInstance.reset(new PackageCommon);
  }

  return s_pInstance.get();
}

//------------------------------------------------------------------------------
void PackageCommon::AddToParser(ParserXBase *pParser)
{
  // Readers that need fancy decorations on their values must
  // be added first (i.e. hex -> "0x...") Otherwise the
  // zero in 0x will be read as a value of zero!
  pParser->AddValueReader(new HexValReader());
  pParser->AddValueReader(new DblValReader());
  pParser->AddValueReader(new BoolValReader());
  pParser->AddValueReader(new BinValReader());

  // Constants
  pParser->DefineConst( _T("pi"), (float_type)MUP_CONST_PI );
  pParser->DefineConst( _T("e"),  (float_type)MUP_CONST_E );

  // Vector
  pParser->DefineFun(new FunSizeOf());

  // Generic functions
  pParser->DefineFun(new FunMax());
  pParser->DefineFun(new FunMin());
  pParser->DefineFun(new FunSum());

  // misc
  pParser->DefineFun(new FunParserID());

  // integer package
  pParser->DefineOprt(new OprtLAnd);
  pParser->DefineOprt(new OprtLOr);
  pParser->DefineOprt(new OprtAnd);
  pParser->DefineOprt(new OprtOr);
  pParser->DefineOprt(new OprtShr);
  pParser->DefineOprt(new OprtShl);

  // booloean package
  pParser->DefineOprt(new OprtLE);
  pParser->DefineOprt(new OprtGE);
  pParser->DefineOprt(new OprtLT);
  pParser->DefineOprt(new OprtGT);
  pParser->DefineOprt(new OprtEQ);
  pParser->DefineOprt(new OprtNEQ);
  pParser->DefineOprt(new OprtBAnd);
  pParser->DefineOprt(new OprtBOr);
  pParser->DefineOprt(new OprtBXor);

  // assignement operators
  pParser->DefineOprt(new OprtAssign);
  pParser->DefineOprt(new OprtAssignAdd);
  pParser->DefineOprt(new OprtAssignSub);
  pParser->DefineOprt(new OprtAssignMul);
  pParser->DefineOprt(new OprtAssignDiv);

  // infix operators
  pParser->DefineInfixOprt(new OprtCastToFloat);
  pParser->DefineInfixOprt(new OprtCastToInt);
}

//------------------------------------------------------------------------------
string_type PackageCommon::GetDesc() const
{
  return _T("");
}

//------------------------------------------------------------------------------
string_type PackageCommon::GetPrefix() const
{
  return _T("");
}

MUP_NAMESPACE_END