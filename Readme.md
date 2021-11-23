![titleimage](http://beltoforion.de/en/muparserx/images/muparserx.jpg)

[![GitHub issues](https://img.shields.io/github/issues/beltoforion/muparserx.svg?maxAge=360)](https://github.com/beltoforion/muparserx/issues)
[![Version](https://img.shields.io/github/release/beltoforion/muparserx.svg?maxAge=360)](https://github.com/beltoforion/muparserx/blob/master/CHANGELOG)
[![Packaging status](https://repology.org/badge/tiny-repos/muparserx.svg)](https://repology.org/project/muparserx/versions)
<!-- [![License](https://img.shields.io/github/license/beltoforion/muparserx.svg?maxAge=360000)](https://github.com/beltoforion/muparserx/blob/master/License.md) -->

muparserx 4.0.11
===========================

The evaluation of a mathematical expression is a standard task required in many applications. It can be solved by either using a standard math expression parser such as muparser or by embedding a scripting language such as Lua. There are however some limitations: Although muparser is pretty fast it will only work with scalar values and although Lua is very flexible it does neither support binary operators for arrays nor complex numbers. So if you need a math expression parser with support for arrays, matrices and strings muparserx may be able to help you.

For details please consult the [muparserx documentation](https://beltoforion.de/en/muparserx)

V4.0.11 (20211123)
-----------------
Bugfixes:
  - Issue 112:  COmpilation issue due to an invalid header file name
 
V4.0.10 (20211122)
-----------------
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


