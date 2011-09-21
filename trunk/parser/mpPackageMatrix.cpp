#include "mpPackageMatrix.h"

#include "mpParserBase.h"
#include "mpFuncMatrix.h"

MUP_NAMESPACE_START

//------------------------------------------------------------------------------
std::auto_ptr<PackageMatrix> PackageMatrix::s_pInstance;

//------------------------------------------------------------------------------
IPackage* PackageMatrix::Instance()
{
  if (s_pInstance.get()==NULL)
  {
    s_pInstance.reset(new PackageMatrix);
  }

  return s_pInstance.get();
}

//------------------------------------------------------------------------------
void PackageMatrix::AddToParser(ParserXBase *pParser)
{
  // Matrix functions
//  pParser->DefineFun(new FunMatrixTrace());
  pParser->DefineFun(new FunMatrixOnes());

  // Matrix Operators
//  pParser->DefineOprt(new OprtMatrixTranspose());
}

//------------------------------------------------------------------------------
string_type PackageMatrix::GetDesc() const
{
  return _T("Operators and functions for matrix operations");
}

//------------------------------------------------------------------------------
string_type PackageMatrix::GetPrefix() const
{
  return _T("");
}

MUP_NAMESPACE_END