# Install script for directory: /home/user/Dokumente/GitHub/muparserx

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/user/Dokumente/GitHub/muparserx/libmuparserx.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/user/Dokumente/GitHub/muparserx/muparserx.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/cmake/muparserx" TYPE FILE FILES
    "/home/user/Dokumente/GitHub/muparserx/cmake/muparserxConfig.cmake"
    "/home/user/Dokumente/GitHub/muparserx/muparserxConfigVersion.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/muparserx" TYPE FILE FILES
    "/home/user/Dokumente/GitHub/muparserx/parser/mpDefines.h"
    "/home/user/Dokumente/GitHub/muparserx/parser/mpError.h"
    "/home/user/Dokumente/GitHub/muparserx/parser/mpFuncCmplx.h"
    "/home/user/Dokumente/GitHub/muparserx/parser/mpFuncCommon.h"
    "/home/user/Dokumente/GitHub/muparserx/parser/mpFuncMatrix.h"
    "/home/user/Dokumente/GitHub/muparserx/parser/mpFuncNonCmplx.h"
    "/home/user/Dokumente/GitHub/muparserx/parser/mpFuncStr.h"
    "/home/user/Dokumente/GitHub/muparserx/parser/mpFwdDecl.h"
    "/home/user/Dokumente/GitHub/muparserx/parser/mpICallback.h"
    "/home/user/Dokumente/GitHub/muparserx/parser/mpIOprt.h"
    "/home/user/Dokumente/GitHub/muparserx/parser/mpIOprtBinShortcut.h"
    "/home/user/Dokumente/GitHub/muparserx/parser/mpIPackage.h"
    "/home/user/Dokumente/GitHub/muparserx/parser/mpIPrecedence.h"
    "/home/user/Dokumente/GitHub/muparserx/parser/mpIToken.h"
    "/home/user/Dokumente/GitHub/muparserx/parser/mpIValReader.h"
    "/home/user/Dokumente/GitHub/muparserx/parser/mpIValue.h"
    "/home/user/Dokumente/GitHub/muparserx/parser/mpIfThenElse.h"
    "/home/user/Dokumente/GitHub/muparserx/parser/mpMatrix.h"
    "/home/user/Dokumente/GitHub/muparserx/parser/mpMatrixError.h"
    "/home/user/Dokumente/GitHub/muparserx/parser/mpOprtBinAssign.h"
    "/home/user/Dokumente/GitHub/muparserx/parser/mpOprtBinCommon.h"
    "/home/user/Dokumente/GitHub/muparserx/parser/mpOprtBinShortcut.h"
    "/home/user/Dokumente/GitHub/muparserx/parser/mpOprtCmplx.h"
    "/home/user/Dokumente/GitHub/muparserx/parser/mpOprtIndex.h"
    "/home/user/Dokumente/GitHub/muparserx/parser/mpOprtMatrix.h"
    "/home/user/Dokumente/GitHub/muparserx/parser/mpOprtNonCmplx.h"
    "/home/user/Dokumente/GitHub/muparserx/parser/mpOprtPostfixCommon.h"
    "/home/user/Dokumente/GitHub/muparserx/parser/mpPackageCmplx.h"
    "/home/user/Dokumente/GitHub/muparserx/parser/mpPackageCommon.h"
    "/home/user/Dokumente/GitHub/muparserx/parser/mpPackageMatrix.h"
    "/home/user/Dokumente/GitHub/muparserx/parser/mpPackageNonCmplx.h"
    "/home/user/Dokumente/GitHub/muparserx/parser/mpPackageStr.h"
    "/home/user/Dokumente/GitHub/muparserx/parser/mpPackageUnit.h"
    "/home/user/Dokumente/GitHub/muparserx/parser/mpParser.h"
    "/home/user/Dokumente/GitHub/muparserx/parser/mpParserBase.h"
    "/home/user/Dokumente/GitHub/muparserx/parser/mpParserMessageProvider.h"
    "/home/user/Dokumente/GitHub/muparserx/parser/mpRPN.h"
    "/home/user/Dokumente/GitHub/muparserx/parser/mpScriptTokens.h"
    "/home/user/Dokumente/GitHub/muparserx/parser/mpStack.h"
    "/home/user/Dokumente/GitHub/muparserx/parser/mpTest.h"
    "/home/user/Dokumente/GitHub/muparserx/parser/mpTokenReader.h"
    "/home/user/Dokumente/GitHub/muparserx/parser/mpTypes.h"
    "/home/user/Dokumente/GitHub/muparserx/parser/mpValReader.h"
    "/home/user/Dokumente/GitHub/muparserx/parser/mpValue.h"
    "/home/user/Dokumente/GitHub/muparserx/parser/mpValueCache.h"
    "/home/user/Dokumente/GitHub/muparserx/parser/mpVariable.h"
    "/home/user/Dokumente/GitHub/muparserx/parser/suSortPred.h"
    "/home/user/Dokumente/GitHub/muparserx/parser/suStringTokens.h"
    "/home/user/Dokumente/GitHub/muparserx/parser/utGeneric.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/user/Dokumente/GitHub/muparserx/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
