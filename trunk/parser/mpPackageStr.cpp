#include "mpPackageStr.h"

#include "mpParserBase.h"
#include "mpFuncStr.h"
#include "mpOprtBinCommon.h"
#include "mpValReader.h"

MUP_NAMESPACE_START

//------------------------------------------------------------------------------
std::auto_ptr<PackageStr> PackageStr::s_pInstance;

//------------------------------------------------------------------------------
IPackage* PackageStr::Instance()
{
  if (s_pInstance.get()==NULL)
  {
    s_pInstance.reset(new PackageStr);
  }

  return s_pInstance.get();
}

//------------------------------------------------------------------------------
void PackageStr::AddToParser(ParserXBase *pParser)
{
  pParser->AddValueReader(new StrValReader());

  // Functions
  pParser->DefineFun(new FunStrLen());
  pParser->DefineFun(new FunStrToDbl());
  pParser->DefineFun(new FunStrToUpper());

  // Operators
  pParser->DefineOprt(new OprtStrAdd);
}

//------------------------------------------------------------------------------
string_type PackageStr::GetDesc() const
{
  return _T("A package for string operations.");
}

//------------------------------------------------------------------------------
string_type PackageStr::GetPrefix() const
{
  return _T("");
}

MUP_NAMESPACE_END