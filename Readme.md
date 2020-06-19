muparserx 4.0.9
===========================
![titleimage](http://beltoforion.de/en/muparser/images/title.jpg)

This is the main repository of muparserx. muparserx is a math expression parser with support
for complex numbers, strings, matrices and vectors. 

For details please consult the [muparserx documentation](https://beltoforion.de/article.php?a=muparserx)

V4.0.9 (20200619)
-----------------
Changes:
  - Copied unit tests from muparser (no new failures)
  - Introduced a maximum expression length of 10000
  - Expressions will be checked for non printable characters
  
Bugfixes:
  - Issue 68: 	Integer test causes floating point exceptions fixed as suggested

V4.0.7 (20160331)
-----------------
Bugfixes:
  - Issue 68: 	Assertion fails (i.e "abs(-3)>abs(2)")
  - untracked issue: cbrt function did not work properly
  - new functions: atan2, reminder, fmod


