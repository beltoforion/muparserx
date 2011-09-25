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
#ifndef MU_PARSER_TEST_H
#define MU_PARSER_TEST_H

#include <string>
#include <numeric> // for accumulate
#include "mpParser.h"
#include "mpOprtBinCommon.h"


MUP_NAMESPACE_START

MUP_BINARY_OPERATOR(DbgSillyAdd, _T("++"), float_type, _T(""), 3, oaLEFT, a+b)

    /** \brief Test cases for unit testing the parser framework.

      (C) 2011 Ingo Berg
    */
    class ParserTester // final
    {
    private:
        static int c_iCount;

        int TestParserValue();
        int TestNames();
        int TestErrorCodes();
        int TestStringFun();
        int TestVector();
        int TestBinOp();
        int TestPostfix();
        int TestInfix();
        int TestEqn();
        int TestMultiArg();
        int TestUndefVar();
        int TestIfElse();
        int TestMultiLine();
        int TestMatrix();
        int TestComplex();

        void Assessment(int a_iNumErr) const;
        void Abort() const;

    public:
        typedef int (ParserTester::*testfun_type)();

	      ParserTester();

        /** \brief Destructor (trivial). */
       ~ParserTester() {};
      	
        /** \brief Copy constructor is deactivated. */
        ParserTester(const ParserTester &a_Obj)
          :m_vTestFun()
          ,m_stream(a_Obj.m_stream)
        {};

	      void Run();

    private:
        std::vector<testfun_type> m_vTestFun;

#if defined(_UNICODE)
        std::wostream *m_stream;
#else
        std::ostream *m_stream;
#endif

	      void AddTest(testfun_type a_pFun);

        // Test Double Parser
        int EqnTest(const string_type &a_str, Value a_val, bool a_fPass, int nExprVar = -1);
        int ThrowTest(const string_type &a_str, int a_nErrc, int a_nPos = -1);
    }; // ParserTester
}  // namespace mu

#endif


