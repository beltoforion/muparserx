#########################################################################
#                                                                       #
#                                                                       #
#                                                                       #
#               __________                                 ____  ___    #
#    _____  __ _\______   \_____ _______  ______ __________\   \/  /    #
#   /     \|  |  \     ___/\__  \\_  __ \/  ___// __ \_  __ \     /     #
#  |  Y Y  \  |  /    |     / __ \|  | \/\___ \\  ___/|  | \/     \     #
#  |__|_|  /____/|____|    (____  /__|  /____  >\___  >__| /___/\  \    #
#        \/                     \/           \/     \/           \_/    #
#                                                                       #
#  Copyright (C) 2011 Ingo Berg                                         #
#                                                                       #
#  Web:     http://muparserx.beltoforion.de                             #
#  SVN:     http://muparserx.googlecode.com/svn/trunk                   #
#  e-mail:  muparserx@beltoforion.de                                    #
#                                                                       #
#                                                                       #
#########################################################################

#########################################################################
#                                                                       #
#  Version history                                                      #
#                                                                       #
#########################################################################

V2.1.0 (20111016)
-----------------
Bugfixes:
  - Complex power operations could introduce small imaginary values in the result
    (i.e. the result of -2^8 was something like "-8 + 9e-19i")

V2.1.0 (20111016)
-----------------
Bugfixes:
  - Issue 1 fixed: Assertion when using a function with multiple arguments 
    		   in the same expression twice with different number of arguments.
                   (Reference: http://code.google.com/p/muparserx/issues/detail?id=1)
  - Issue 2 fixed: DblValReader::IsValue broken for numbers at the end of the string

V2.0.0 (20111009)
-----------------

Changes:
- Fundamental datatype changed to a matrix type instead of a vector type
- Multidimensional index operator added
  old:
	"m[1][2] = 1"
  new:
	"m[1,2] = 1"

- type identifier for matrices is now 'm', formerly 'a' was used to 
  indicate arrays. An arrays are now seen as subsets of matrices, there is no 
  special type for arrays.

Bugfixes:
- Matrix addition and subtraction work properly now.


V1.10.2 (20110911)
------------------
Bugfixes:
- Fix for changed behaviour of tellg in GCC 4.6.1. A Space is now appended 
  to every expression in order to avoid problems.


V1.10 (20110310)
----------------
Warning:
The API of this version is not backwards compatible and requires minor 
changes to client code!

Changes:
- Static type checking removed entirely
  (All type checking must be made at runtime by the callbacks themself)
- Optimizer removed. The optimizer had only limited effect since it only
  implemented a very simple constant folding mechanism. It collided with 
  the new if-then-else logic and had to go. It will probably be reintroduced
  in one of the next versions using a different implementation.
- Expressions can now span multiple lines. This only makes sense when used
  together with the assignment operator i.e.:

		a=1
		b=2
		c=3
		sin(a+b+c)


Bugfixes:
- Nested if-then-else did not work properly
- Sign operators extended to work with arrays
- Operators "==" and "!=" did not work properly for arrays
- Relational operators "<", ">", "<=", ">=" did not work for complex numbers
- GCC makefile was broken in V1.09
- complex multiplication did not work correctly; 
  was:
	 (a+ib)(c+id)=>re=ac-bd;im=ad-bc 
  instead of:
         (a+ib)(c+id)=>re=ac-bd;im=ad+bc 
- Expressions with parameterless functions like a=foo() did not evaluate properly.


V1.09 (20101120)
----------------
Changes:
- Performance increased by factor 4 due to introducing a simple memory pool for value items.
- C++ like if-then-else operator added ( "(a<b) ? c : d")

Bugfixes:
- Memory leak fixed which prevented operator and funtion items from beeing released.


V1.08 (20100902)
----------------
Changes:
- Implicit creation of unknown variables at parser runtime is now possibe
  (i.e. expressions like "a=0"; with a beeing a undefined variable).
- Callbacks can now be organized in packages
- Callbacks split into a complex and a non complex package
- Complex power operator added

Bugfixes:
- Assignment operators did not work properly for complex values
- Complex sign operator fixed in order not to mess up 0 by
  multiplying it with -1 (-0 and 0 ar not the same according to
  IEEE754) 


V1.07 (20100818)
----------------
Changes:
- Parsing performance improved by 20 - 30 % due to removing unnecessary 
  copy constructor calls when returning the final result.
- License changed from GPLv3 to LGPLv3
- Assignment to vector elements is now possible (i.e.: va[1]=9)

Bugfixes:
- The Value type could not properly handle matrices (vector of vector)
  uses the reverse polish notation of an expression for the evaluation.
- Error messages did not display the proper type id's when compiled 
  with UNICODE support.


V1.06 (20100710)
----------------
- Parsing performance improved by factor 2-3 due to a change which
  uses the reverse polish notation of an expression for the evaluation.


V1.05 (20100530)
----------------
- The parser now handles the associativity of binary operators properly
- Parsing performance improved by factor 7 due to caching tokens 
  once an expression is parsed. Successive evaluations will use 
  the cached tokens instead of parsing from string again.


V1.04 (20100516):
-----------------
- Querying of expression variables implemented
- Bugfix for incorrect evaluation of expressions using the index 
  operator added
- nil values removed
- Support for functions without parameters added
- UNICODE support added


V1.03:
------
- basic functions rewritten to complex valued functions
- Unit postfix operators added to the standard setup


V1.02:
------
- Index operator added
- addition/subtraction of vectors added


V1.01:
------
- Complex numbers added with support for basic binary operators
- Vector type added with support for basic operations (v*v, v+v)
- Variable class changed to take a pointer to a value class instead
  of base types like int or double.


#########################################################################
#                                                                       #
#  Licence                                                              #
#                                                                       #
#########################################################################


muParserX 
Copyright (c) 2012, Ingo Berg
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted 
provided that the following conditions are met:

   * Redistributions of source code must retain the above copyright notice, this list of 
     conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright notice, this list of 
     conditions and the following disclaimer in the documentation and/or other materials provided 
	 with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR 
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND 
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER 
IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

