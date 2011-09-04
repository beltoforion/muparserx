/*
               __________                                 ____  ___
    _____  __ _\______   \_____ _______  ______ __________\   \/  /
   /     \|  |  \     ___/\__  \\_  __ \/  ___// __ \_  __ \     / 
  |  Y Y  \  |  /    |     / __ \|  | \/\___ \\  ___/|  | \/     \ 
  |__|_|  /____/|____|    (____  /__|  /____  >\___  >__| /___/\  \
        \/                     \/           \/     \/           \_/

  muParserX - A C++ math parser library with array and string support
  Copyright 2010 Ingo Berg

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU LESSER GENERAL PUBLIC LICENSE
  as published by the Free Software Foundation, either version 3 of 
  the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with this program.  If not, see http://www.gnu.org/licenses.
*/
#include "mpParser.h"

//--- Standard includes ----------------------------------------------------
#include <cmath>
#include <algorithm>
#include <numeric>

//--- Parser framework -----------------------------------------------------
#include "mpPackageUnit.h"
#include "mpPackageStr.h"
#include "mpPackageCmplx.h"
#include "mpPackageNonCmplx.h"
#include "mpPackageCommon.h"


using namespace std;


/** \brief Namespace for mathematical applications. */
MUP_NAMESPACE_START

  //---------------------------------------------------------------------------
  /** \brief Default constructor. 

    Call ParserXBase class constructor and initiate function, operator 
    and constant initialization.
  */
  ParserX::ParserX(EPackages ePackages)
    :ParserXBase()
  {
    DefineNameChars(_T("0123456789_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"));
    DefineOprtChars(_T("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ+-*^/?<>=#!$%&|~'_µ{}"));
    DefineInfixOprtChars(_T("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ()/+-*^?<>=#!$%&|~'_"));

    if (ePackages & pckUNIT)
      AddPackage(PackageUnit::Instance());

    if (ePackages & pckSTRING)
      AddPackage(PackageStr::Instance());

    if (ePackages & pckCOMPLEX)
      AddPackage(PackageCmplx::Instance());

    if (ePackages & pckNON_COMPLEX)
      AddPackage(PackageNonCmplx::Instance());

    if (ePackages & pckCOMMON)
      AddPackage(PackageCommon::Instance());
  }
} // namespace mu
