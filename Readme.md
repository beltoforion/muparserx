muparserx 4.0.9
===========================
.. image:: http://beltoforion.de/en/muparser/images/title.jpg

V4.0.9 (20200619)
-----------------
Bugfixes:
  - Issue 68: 	Integer test causes floating point exceptions fixed as suggested

V4.0.7 (20160331)
-----------------
Bugfixes:
  - Issue 68: 	Assertion fails (i.e "abs(-3)>abs(2)")
  - untracked issue: cbrt function did not work properly
  - new functions: atan2, reminder, fmod
  
V4.0.5 (20151120)
-----------------

Changes:
  - New Noncomplex Functions:	cbrt  - Cubic root
                                hypot - Length of a 2d vector
                                pow   - Power function
  - New complex functions:      pow   - Power function
  - Value construction and assignment from int is supported again (removed
    when going from in 3.x to 4.x).

V4.0.4 (20151015)
-----------------

Bugfixes:
  - Issue 59, 60, 61, 63: Various segfaults/assertions for unexpected 
                          input        
  - Issue 55, 56, 57, 58: Various issued related to a failure to detect 
                          missing brackets.

V4.0.0 (20150622)
-----------------

API changes:
  - removed value and variable constructors from integer types. There was 
    some confusion about the extend of support for integers (see Issue 
    #36). Internally muparserx is always using floating point values even 
    when dealing with integer numbers. There is no point in the API 
    pretending to have real integer support.
