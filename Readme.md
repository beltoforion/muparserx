![_title](https://user-images.githubusercontent.com/2202567/196066131-a421b3c0-20e0-46e7-88ee-15ae29b215cd.jpg)

[![GitHub issues](https://img.shields.io/github/issues/beltoforion/muparserx.svg?maxAge=360)](https://github.com/beltoforion/muparserx/issues)
[![Version](https://img.shields.io/github/release/beltoforion/muparserx.svg?maxAge=360)](https://github.com/beltoforion/muparserx/blob/master/CHANGELOG)
[![Packaging status](https://repology.org/badge/tiny-repos/muparserx.svg)](https://repology.org/project/muparserx/versions)
<!-- [![License](https://img.shields.io/github/license/beltoforion/muparserx.svg?maxAge=360000)](https://github.com/beltoforion/muparserx/blob/master/License.md) -->

muparserx
===========================

V4.0.12 (20230304)
------------------
Bugfixes:
  - Issue 116: Changed implementation of parsing double values to fix #116 on Mac.
  - Issue 115: String constants starting woth "or" confused with operator during parsing step
  - Issue 117: Equals operator behavior inconsistent when checking boolean values. (no type check) 
  
Changes:
  - C++17 is now the minimum required C++ version to compile the code
  - added a wide string option to cmake (USE_WIDE_STRING)
  - removed compatibility fixes for older compilers (mostly MSVC)
  - fixed compiler warnings 

V4.0.11 (20211123)
------------------
Bugfixes:
  - Issue 112:  Compilation issue due to an invalid header file name
 
V4.0.10 (20211122)
------------------
Bugfixes:
  - Issue 107:  Complex multiplication-assignment did not work correctly
  - Issue 110:  Short evaluation for binary operators added (thanks to user egyptyu)
  
V4.0.9 (20200619)
-----------------
Changes:
  - Copied unit tests from muparser (no new failures)
  - Introduced a maximum expression length of 10000
  - Expressions will be checked for non printable characters
  
Bugfixes:
  - Issue 68: 	Integer test causes floating point exceptions; fixed as suggested

V4.0.8 (20181218)
-----------------
Changes:
  - Build system changed to CMake

V4.0.7 (20160331)
-----------------
Bugfixes:
  - Issue 68: 	Assertion fails (i.e "abs(-3)>abs(2)")
  - untracked issue: cbrt function did not work properly
  - new functions: atan2, reminder, fmod


