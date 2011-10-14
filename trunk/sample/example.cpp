/** \example example.cpp

<pre>
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
  </pre>

  This is example code showing you how to use muParserX.
*/

//---------------------------------------------------------------------------
//
//  muParserX 
//
//  example.cpp - Demonstrates how to use muParserX
//
//---------------------------------------------------------------------------

/** \brief This macro will enable mathematical constants like M_PI. */
#define _USE_MATH_DEFINES		

//--- Standard include ------------------------------------------------------
#if defined(_WIN32) && defined(_DEBUG)
  #define _CRTDBG_MAP_ALLOC
  #include <stdlib.h>
  #include <crtdbg.h>
  #define CREATE_LEAKAGE_REPORT
#endif

#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cstdio>
#include <cmath>
#include <string>
#include <iostream>

//--- muParserX framework ---------------------------------------------------
#include "mpParser.h"
#include "mpDefines.h"
#include "mpTest.h"

//--- other includes --------------------------------------------------------
#include "timer.h"

using namespace std;
using namespace mup;

#if defined(CREATE_LEAKAGE_REPORT)

// Dumping memory leaks in the destructor of the static guard
// guarantees i won't get false positives from the ParserErrorMsg 
// class wich is a singleton with a static instance.
struct DumpLeaks
{
 ~DumpLeaks()
  {
    _CrtDumpMemoryLeaks();
  }
} static LeakDumper;

#endif

const string_type sPrompt = _T("muParserX> ");

//-------------------------------------------------------------------------------------------------
// The following classes will be used to list muParserX variables, constants
// from this console application
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
class FunPrint : public ICallback
{
public:
  FunPrint() : ICallback(cmFUNC, _T("print"), 1) 
  {}

  virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc)
  {
    ParserXBase &parser = *GetParent();
    console() << a_pArg[0].Get()->ToString() << _T("\n");
    *ret = 0;
  }

  virtual const char_type* GetDesc() const
  {
    return _T("");
  }
  
  virtual IToken* Clone() const
  {
    return new FunPrint();
  }
}; // class FunPrint

//-------------------------------------------------------------------------------------------------
class FunTest0 : public ICallback
{
public:
  FunTest0() : ICallback(cmFUNC, _T("test0"), 0) 
  {}

  virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc)
  {
    ParserXBase &parser = *GetParent();
    *ret = 0;
  }

  virtual const char_type* GetDesc() const
  {
    return _T("");
  }
  
  virtual IToken* Clone() const
  {
    return new FunTest0();
  }
}; // class FunTest0

//-------------------------------------------------------------------------------------------------
class FunListVar : public ICallback
{
public:

  FunListVar() : ICallback(cmFUNC, _T("list_var"), 0) 
  {}

  virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc)
  {
    ParserXBase &parser = *GetParent();

    console() << _T("\nParser variables:\n");
    console() << _T(  "-----------------\n");

    // Query the used variables (must be done after calc)
    var_maptype vmap = parser.GetVar();
    if (!vmap.size())
    {
      console() << _T("Expression does not contain variables\n");
    }
    else
    {
      var_maptype::iterator item = vmap.begin();
      for (; item!=vmap.end(); ++item)
      {
        // You can dump the token into a stream via the "<<" operator
        console() << _T("  ") << item->first << _T(" =  ") << *(item->second)/* << _T("\n")*/;

        // If you need more specific information cast the token to a variable object
        Variable &v = (Variable&)(*(item->second));
        console() << _T("  (type=\"") << v.GetType() << _T("\"; ptr=0x") << hex << v.GetPtr() << _T(")\n");
      }
    }

    *ret = (int)vmap.size();
  }

  virtual const char_type* GetDesc() const
  {
    return _T("list_var() - List all variables of the parser bound to this function and returns the number of defined variables.");
  }

  virtual IToken* Clone() const
  {
    return new FunListVar();
  }
}; // class FunListVar


//-------------------------------------------------------------------------------------------------
class FunListConst : public ICallback
{
public:

  FunListConst() : ICallback(cmFUNC, _T("list_const"), 0) 
  {}

  virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc)
  {
    ParserXBase &parser = *GetParent();

    console() << _T("\nParser constants:\n");
    console() << _T(  "-----------------\n");

    val_maptype cmap = parser.GetConst();
    if (!cmap.size())
    {
      console() << _T("No constants defined\n");
    }
    else
    {
      val_maptype::iterator item = cmap.begin();
      for (; item!=cmap.end(); ++item)
        console() << _T("  ") << item->first << _T(" =  ") << (Value&)(*(item->second)) << _T("\n");
    }

    *ret = (int)cmap.size();
  }

  virtual const char_type* GetDesc() const
  {
    return _T("list_const() - List all constants of the parser bound to this function and returns the number of defined constants.");
  }

  virtual IToken* Clone() const
  {
    return new FunListConst();
  }
}; // class FunListConst


//-------------------------------------------------------------------------------------------------
class FunBenchmark : public ICallback
{
public:
  FunBenchmark() : ICallback(cmFUNC, _T("bench"), 0) 
  {}

  virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc)
  {
    char outstr[200];
    time_t t = time(NULL);

    #ifdef _DEBUG
    strftime(outstr, sizeof(outstr), "Result_%Y%m%d_%H%M%S_dbg.txt", localtime(&t));
    #else
    strftime(outstr, sizeof(outstr), "Result_%Y%m%d_%H%M%S_release.txt", localtime(&t));
    #endif

    const char_type* sExpr[] = { 
                                 _T("sin(a)"),
                                 _T("cos(a)"),
                                 _T("tan(a)"),
                                 _T("sqrt(a)"),
                                 _T("(a+b)*3"),
                                 _T("a^2+b^2"),
                                 _T("a^3+b^3"),
                                 _T("a^4+b^4"),
                                 _T("a^5+b^5"),
                                 _T("a*2+b*2"),
                                 _T("-(b^1.1)"),
                                 _T("a + b * c"),
                                 _T("a * b + c"),
                                 _T("a+b*(a+b)"),
                                 _T("(1+b)*(-3)"),
                                 _T("e^log(7*a)"),
                                 _T("10^log(3+b)"),
                                 _T("a+b-e*pi/5^6"),
                                 _T("a^b/e*pi-5+6"),
                                 _T("sin(a)+sin(b)"),
                                 _T("(cos(2.41)/b)"),
                                 _T("-(sin(pi+a)+1)"),
                                 _T("a-(e^(log(7+b)))"),
                                 _T("sin(((a-a)+b)+a)"),
                                 _T("((0.09/a)+2.58)-1.67"),
                                 _T("abs(sin(sqrt(a^2+b^2))*255)"),
                                 _T("abs(sin(sqrt(a*a+b*b))*255)"),
                                 _T("cos(0.90-((cos(b)/2.89)/e)/a)"),
                                 _T("(1*(2*(3*(4*(5*(6*(a+b)))))))"),
                                 _T("abs(sin(sqrt(a^2.1+b^2.1))*255)"),
                                 _T("(1*(2*(3*(4*(5*(6*(7*(a+b))))))))"),
                                 _T("1/(a*sqrt(2*pi))*e^(-0.5*((b-a)/a)^2)"),
                                 _T("1+2-3*4/5^6*(2*(1-5+(3*7^9)*(4+6*7-3)))+12"),
                                 _T("1+b-3*4/5^6*(2*(1-5+(3*7^9)*(4+6*7-3)))+12*a"),
                                 _T("(b+1)*(b+2)*(b+3)*(b+4)*(b+5)*(b+6)*(b+7)*(b+8)*(b+9)*(b+10)*(b+11)*(b+12)"),
                                 _T("(a/((((b+(((e*(((((pi*((((3.45*((pi+a)+pi))+b)+b)*a))+0.68)+e)+a)/a))+a)+b))+b)*a)-pi))"),
                                 _T("(((-9))-e/(((((((pi-(((-7)+(-3)/4/e))))/(((-5))-2)-((pi+(-0))*(sqrt((e+e))*(-8))*(((-pi)+(-pi)-(-9)*(6*5))/(-e)-e))/2)/((((sqrt(2/(-e)+6)-(4-2))+((5/(-2))/(1*(-pi)+3))/8)*pi*((pi/((-2)/(-6)*1*(-1))*(-6)+(-e)))))/((e+(-2)+(-e)*((((-3)*9+(-e)))+(-9)))))))-((((e-7+(((5/pi-(3/1+pi)))))/e)/(-5))/(sqrt((((((1+(-7))))+((((-e)*(-e)))-8))*(-5)/((-e)))*(-6)-((((((-2)-(-9)-(-e)-1)/3))))/(sqrt((8+(e-((-6))+(9*(-9))))*(((3+2-8))*(7+6+(-5))+((0/(-e)*(-pi))+7)))+(((((-e)/e/e)+((-6)*5)*e+(3+(-5)/pi))))+pi))/sqrt((((9))+((((pi))-8+2))+pi))/e*4)*((-5)/(((-pi))*(sqrt(e)))))-(((((((-e)*(e)-pi))/4+(pi)*(-9)))))))+(-pi)"),
                                 0 };



    ParserX  parser;      
    Value a((float_type)1.0);
    Value b((float_type)2.0);
    Value c((float_type)3.0);

    parser.DefineVar(_T("a"),  Variable(&a));
    parser.DefineVar(_T("b"),  Variable(&b));
    parser.DefineVar(_T("c"),  Variable(&c));
    parser.DefineConst(_T("pi"), (float_type)M_PI);
    parser.DefineConst(_T("e"), (float_type)M_E);

    FILE *pFile = fopen(outstr, "w");
    int iCount = 400000;

    #ifdef _DEBUG
    string_type sMode = _T("# debug mode\n");
    #else
    string_type sMode = _T("# release mode\n");
    #endif

    fprintf(pFile, "%s; muParserX V%s\n", sMode.c_str(), ParserXBase::GetVersion().c_str());
    fprintf(pFile, "\"Eqn no.\", \"number\", \"result\", \"time in ms\", \"eval per second\", \"expr\"\n");

    printf("%s", sMode.c_str());
    printf("\"Eqn no.\", \"number\", \"result\", \"time in ms\", \"eval per second\", \"expr\"\n");

    double avg_eval_per_sec = 0;
    int ct=0;
    for (int i=0; sExpr[i]; ++i)
    {
      ct++;
      StartTimer();
      Value val;
      parser.SetExpr(sExpr[i]);

      // implicitely create reverse polish notation
      parser.Eval(); 

      for (int n=0; n<iCount; ++n)
      {
        val = parser.Eval();
      }

      double diff = StopTimer();
      
      float_type eval_per_sec = (float_type)iCount*1000.0/diff;
      avg_eval_per_sec += eval_per_sec;

      #if !defined _UNICODE
      fprintf(pFile, "Eqn_%d, %d, %lf, %lf, %lf, %s\n", i, iCount, val.GetFloat(), diff, eval_per_sec, sExpr[i]);
      printf("Eqn_%d, %d, %lf, %lf, %lf, %s\n"        , i, iCount, val.GetFloat(), diff, eval_per_sec, sExpr[i]);
      #else
      fwprintf(pFile, _T("Eqn_%d, %d, %lf, %lf, %lf, %s\n"), i, iCount, val.GetFloat(), diff, eval_per_sec, sExpr[i]);
      wprintf(_T("Eqn_%d, %d, %lf, %lf, %lf, %s\n")        , i, iCount, val.GetFloat(), diff, eval_per_sec, sExpr[i]);
      #endif
    }

    avg_eval_per_sec /= (float_type)ct;

    fprintf(pFile, "# Eval per s: %d", (long)avg_eval_per_sec);

    fflush(pFile);
    *ret = (float_type)avg_eval_per_sec;
  }

  virtual const char_type* GetDesc() const
  {
    return _T("bench() - Perform a benchmark with a set of standard functions.");
  }
  
  virtual IToken* Clone() const
  {
    return new FunBenchmark();
  }
}; // class FunBenchmark


//-------------------------------------------------------------------------------------------------
class FunListFunctions : public ICallback
{
public:
  FunListFunctions() : ICallback(cmFUNC, _T("list_fun"), 0) 
  {}

  virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc)
  {
    ParserXBase &parser = *GetParent();

    console() << _T("\nParser functions:\n");
    console() << _T(  "----------------\n");

    fun_maptype fmap = parser.GetFunDef();
    if (!fmap.size())
    {
      console() << _T("No functions defined\n");
    }
    else
    {
      val_maptype::iterator item = fmap.begin();
      for (; item!=fmap.end(); ++item)
      {
        ICallback *pFun = (ICallback*)item->second.Get();
        console() << pFun->GetDesc() << _T("\n");
      }
    }

    *ret = (int)fmap.size();
  }

  virtual const char_type* GetDesc() const
  {
    return _T("list_fun() - List all parser functions and returns the total number of defined functions.");
  }
  
  virtual IToken* Clone() const
  {
    return new FunListFunctions();
  }
}; // class FunListFunctions


//-------------------------------------------------------------------------------------------------
class FunEnableOptimizer : public ICallback
{
public:
  FunEnableOptimizer() : ICallback(cmFUNC, _T("enable_optimizer"), 1) 
  {}

  virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc)
  {
    ParserXBase &parser = *GetParent();
    parser.EnableOptimizer(a_pArg[0]->GetBool());
    *ret = a_pArg[0]->GetBool();
  }
  virtual const char_type* GetDesc() const
  {
    return _T("enable_optimizer(bool) - Enables the parsers built in expression optimizer.");
  }
  
  virtual IToken* Clone() const
  {
    return new FunEnableOptimizer();
  }
}; // class FunListFunctions


//-------------------------------------------------------------------------------------------------
class FunSelfTest : public ICallback
{
public:
  FunSelfTest() : ICallback(cmFUNC, _T("test"), 0) 
  {}

  virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc)
  {
    ParserXBase::EnableDebugDump(0, 0);
    ParserTester pt;
    pt.Run();
    *ret = 0;
  }
  virtual const char_type* GetDesc() const
  {
    return _T("test() - Runs the unit test of muparserx.");
  }
  
  virtual IToken* Clone() const
  {
    return new FunSelfTest();
  }
}; // class FunSelfTest

//-------------------------------------------------------------------------------------------------
class FunEnableDebugDump : public ICallback
{
public:
  FunEnableDebugDump() : ICallback(cmFUNC, _T("dump"), 2) 
  {}

  virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc)
  {
    ParserXBase::EnableDebugDump(a_pArg[0]->GetBool(), a_pArg[1]->GetBool());
    *ret = 0;
  }
  virtual const char_type* GetDesc() const
  {
    return _T("dump(bDumpRPN, bDumpStack) - Enable dumping of RPN and stack content.");
  }
  
  virtual IToken* Clone() const
  {
    return new FunEnableDebugDump();
  }
}; // class FunEnableDebugDump



/*
//-------------------------------------------------------------------------------------------------
class FunGeneric : public ICallback
{
public:

  FunGeneric(string_type sIdent, string_type sFunction) 
    :ICallback(cmFUNC, sIdent.c_str()) 
    ,m_parser()
    ,m_vars()
    ,m_val()
  {
    m_parser.SetExpr(sFunction);
    m_vars = m_parser.GetExprVar();
    SetArgc(m_vars.size());

    // Create values for the undefined variables and bind them
    // to the variables
    var_maptype::iterator item = m_vars.begin();
    for (; item!=m_vars.end(); ++item)
    {
      ptr_val_type val(new Value());
      m_val.push_back(val);

      // assign a parser variable
      m_parser.DefineVar(item->second->GetIdent(), Variable(val.Get()));
    }
  }

  virtual ~FunGeneric()
  {}

  virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc)
  {
    // Set the variables
    for (std::size_t i=0; i<(std::size_t)a_iArgc; ++i)
    {
      *m_val[i] = *a_pArg[i];
    }

    *ret = m_parser.Eval();
  }

  virtual const char_type* GetDesc() const
  {
    return _T("xxx(...) - Dynamically defined function");
  }
  
  virtual IToken* Clone() const
  {
    return new FunGeneric(*this);
  }

private:

  ParserX m_parser;
  mup::var_maptype m_vars;
  val_vec_type m_val;
}; // class FunGeneric

//---------------------------------------------------------------------------
class FunDefine : public ICallback
{
public:
  FunDefine() : ICallback(cmFUNC, _T("define"), 2) 
  {}

  virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc)
  {
    string_type sFun = a_pArg[0]->GetString();
    string_type sDef = a_pArg[1]->GetString();

    ParserXBase &parser = *GetParent();
    parser.DefineFun(new FunGeneric(sFun, sDef));

    *ret = 0;
  }

  virtual const char_type* GetDesc() const
  {
    return _T("define(Function, Definition) - Define a new parser function.");
  }
  
  virtual IToken* Clone() const
  {
    return new FunDefine();
  }
}; // class FunDefine

//---------------------------------------------------------------------------
class FunDerive : public ICallback
{
public:
  FunDerive() : ICallback(cmFUNC, _T("derive")) 
  {}

  virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc)
  {
    *ret = 0;
  }

  virtual const char_type* GetDesc() const
  {
    return _T("...");
  }

  void Compile(const string_type &sArg)
  {
  }

  virtual IToken* Clone() const
  {
    return new FunDerive();
  }
}; // class FunDerive
*/


//---------------------------------------------------------------------------
void SelfTest()
{
  console() << _T("-------------------------------------------------------------------------\n\n");
  console() << _T("               __________                                 ____  ___\n");
  console() << _T("    _____  __ _\\______   \\_____ _______  ______ __________\\   \\/  /\n");
  console() << _T("   /     \\|  |  \\     ___/\\__  \\\\_  __ \\/  ___// __ \\_  __ \\     / \n");
  console() << _T("  |  Y Y  \\  |  /    |     / __ \\|  | \\/\\___ \\\\  ___/|  | \\/     \\ \n");
  console() << _T("  |__|_|  /____/|____|    (____  /__|  /____  >\\___  >__| /___/\\  \\\n");
  console() << _T("        \\/                     \\/           \\/     \\/           \\_/\n");


  console() << _T("  Version ") << ParserXBase::GetVersion() << _T("\n");
  console() << _T("  Copyright (C) 2011 Ingo Berg");
  console() << _T("\n");

  console() << _T("-------------------------------------------------------------------------\n\n");
  console() << _T( "Configuration:\n\n");

#if defined(_DEBUG)
  console() << _T( "- DEBUG build\n");
#else
  console() << _T( "- RELEASE build\n");
#endif

  console() << _T( "- ") << sizeof(void*)*8 << _T(" bit\n");

#if defined(_UNICODE)
  console() << _T( "- UNICODE build\n");
#else  
  console() << _T( "- ASCII build\n");
#endif

  console() << _T("-------------------------------------------------------------------------\n\n");
  console() << _T( "Running test suite:\n\n");

  ParserTester pt;
  pt.Run();

  console() << _T("-------------------------------------------------------------------------\n\n");
  console() << _T("Special parser functions:\n");
  console() << _T("  list_var()   - list parser variables and return the number of variables.\n");
  console() << _T("  list_fun()   - list parser functions and return  the number of functions\n");
  console() << _T("  list_const() - list all numeric parser constants\n");
  console() << _T("Command line commands:\n");
  console() << _T("  exprvar      - list all variables found in the last expression\n");
  console() << _T("  rpn          - Dump reverse polish notation of the current expression\n");
  console() << _T("  quit         - exits the parser\n");
  console() << _T("Constants:\n");
  console() << _T("  \"e\"   2.718281828459045235360287\n");
  console() << _T("  \"pi\"  3.141592653589793238462643\n");
  console() << _T("-------------------------------------------------------------------------\n\n");
}

//---------------------------------------------------------------------------
void ListExprVar(ParserXBase &parser)
{
  console() << _T("\nVariables found in : \"") << parser.GetExpr() << _T("\"\n");
  console() << _T(  "-----------------------------\n");

  // Query the used variables (must be done after calc)
  var_maptype vmap = parser.GetExprVar();
  if (!vmap.size())
  {
    console() << _T("Expression does not contain variables\n");
  }
  else
  {
    var_maptype::iterator item = vmap.begin();
    for (; item!=vmap.end(); ++item)
      console() << _T("  ") << item->first << _T(" =  ") << (Variable&)(*(item->second)) << _T("\n");
  }
}

//---------------------------------------------------------------------------
/** \brief Check for external keywords.
*/
int CheckKeywords(const char_type *a_szLine, ParserXBase &a_Parser)
{
  string_type sLine(a_szLine);

  if (sLine==_T("quit"))
  {
    return -1;
  }
  else if (sLine==_T("exprvar"))
  {
    ListExprVar(a_Parser);
    return 1;
  }
  else if (sLine==_T("rpn"))
  {
    a_Parser.DumpRPN();
    return 1;
  }

  return 0;
}

//---------------------------------------------------------------------------
void Calc()
{
//  ParserX  parser(pckALL_NON_COMPLEX);
  ParserX  parser(pckALL_COMPLEX);

  // Create an array variable
  Value arr1(3, 0);
  arr1.At(0) = (float_type)1.0;
  arr1.At(1) = (float_type)2.0;
  arr1.At(2) = (float_type)3.0;

  Value arr2(3, 0);
  arr2.At(0) = (float_type)4.0;
  arr2.At(1) = (float_type)3.0;
  arr2.At(2) = (float_type)2.0;

  Value arr3(4, 0);
  arr3.At(0) = (float_type)1.0;
  arr3.At(1) = (float_type)2.0;
  arr3.At(2) = (float_type)3.0;
  arr3.At(3) = (float_type)4.0;

  Value arr4(3, 0);
  arr4.At(0) = (float_type)4.0;
  arr4.At(1) = false;
  arr4.At(2) = _T("hallo");

  // Create a 3x3 matrix with zero elements
  Value m1(3, 3, 0);
  m1.At(0, 0) = 1;
  m1.At(1, 1) = 1;
  m1.At(2, 2) = 1;

  Value m2(3, 3, 0);
  m2.At(0, 0) = 1;
  m2.At(0, 1) = 2;
  m2.At(0, 2) = 3;
  m2.At(1, 0) = 4;
  m2.At(1, 1) = 5;
  m2.At(1, 2) = 6;
  m2.At(2, 0) = 7;
  m2.At(2, 1) = 8;
  m2.At(2, 2) = 9;

  Value val[5];
  val[0] = (float_type)1.1;
  val[1] = 1;
  val[2] = false;
  val[3] = _T("Hello");
  val[4] = _T("World");

  Value fVal[3];
  fVal[0] = (float_type)1.11;
  fVal[1] = (float_type)2.22;
  fVal[2] = (float_type)3.33;

  Value iVal[3];
  iVal[0] = 1;
  iVal[1] = 2;
  iVal[2] = 3;

  Value sVal[3];
  sVal[0] = _T("hello");
  sVal[1] = _T("world");
  sVal[2] = _T("test");

  Value cVal[3];
  cVal[0] = mup::cmplx_type(1, 1);
  cVal[1] = mup::cmplx_type(2, 2);
  cVal[2] = mup::cmplx_type(3, 3);

  Value ans;
  parser.DefineVar(_T("ans"), Variable(&ans));

  // some tests for vectors
  parser.DefineVar(_T("va"), Variable(&arr1));
  parser.DefineVar(_T("vb"), Variable(&arr2));
  parser.DefineVar(_T("vc"), Variable(&arr3));
  parser.DefineVar(_T("vd"), Variable(&arr4));
  parser.DefineVar(_T("m1"), Variable(&m1));
  parser.DefineVar(_T("m2"), Variable(&m2));

  parser.DefineVar(_T("a"),  Variable(&fVal[0]));
  parser.DefineVar(_T("b"),  Variable(&fVal[1]));
  parser.DefineVar(_T("c"),  Variable(&fVal[2]));

  parser.DefineVar(_T("ia"), Variable(&iVal[0]));
  parser.DefineVar(_T("ib"), Variable(&iVal[1]));
  parser.DefineVar(_T("ic"), Variable(&iVal[2]));

  parser.DefineVar(_T("ca"), Variable(&cVal[0]));
  parser.DefineVar(_T("cb"), Variable(&cVal[1]));
  parser.DefineVar(_T("cc"), Variable(&cVal[2]));

  parser.DefineVar(_T("sa"), Variable(&sVal[0]));
  parser.DefineVar(_T("sb"), Variable(&sVal[1]));

  // Add functions for inspecting the parser properties
  parser.DefineFun(new FunListVar);
  parser.DefineFun(new FunListFunctions);
  parser.DefineFun(new FunListConst);
  parser.DefineFun(new FunBenchmark);
  parser.DefineFun(new FunEnableOptimizer);
  parser.DefineFun(new FunSelfTest);
  parser.DefineFun(new FunEnableDebugDump);
  parser.DefineFun(new FunTest0);
  parser.DefineFun(new FunPrint);
 
  parser.EnableAutoCreateVar(true);

//#ifdef _DEBUG
//  ParserXBase::EnableDebugDump(1, 0);
//#endif

  for(;;)
  {
    try
    {
      console() << sPrompt;

      string_type sLine;
      std::getline(mup::console_in(), sLine);
      if (sLine.length()==0)
        continue;

      if (sLine==_T("dbg"))
      {
        sLine  = _T("sum(3)/sum(3,4,5)");
        mup::console() << sLine << endl;
      }

      switch(CheckKeywords(sLine.c_str(), parser)) 
      {
      case  0: break;
      case  1: continue;
      case -1: return;
      }
    
      parser.SetExpr(sLine);

      // The returned result is of type Value, value is a Variant like
      // type that can be either a boolean an integer or a floating point value
      ans = parser.Eval();
//      ans = parser.Eval();

      // Value supports C++ streaming like this:
      //console() << _T("Result (type: '" << ans.GetType() <<  "'):\n");
      console() << _T("ans = ") << ans << _T("\n");

      // Or if you need the specific type use this:
      //switch (result.GetType())
      //{
      //case 's': cout << result.GetString() << " (string)" << "\n"; break;
      //case 'i': cout << result.GetInt() << " (int)" << "\n"; break;
      //case 'f': cout << result.GetFloat() << " (float)" << "\n"; break;
      //case 'c': cout << result.GetFloat() << "+" << result.GetImag() << "i (complex)" << "\n"; break;
      //case 'b': break;
      //}
    }
    catch(ParserError &e)
    {
      if (e.GetPos()!=-1)
      {
        string_type sMarker;
        sMarker.insert(0, sPrompt.size() + e.GetPos(), ' ');
        sMarker += _T("^\n");
        console() << sMarker;
      }

      console() << e.GetMsg() << _T(" (Errc: ") << e.GetCode() << _T(")") << _T("\n\n");

      //if (e.GetContext().Ident.length()) 
      //  console() << _T("Ident.: ") << e.GetContext().Ident << _T("\n");

      //if (e.GetToken().length()) 
      //  console() << _T("Token: \"") << e.GetToken() << _T("\"\n");
    } // try / catch
  } // for (;;)
}

//---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
  SelfTest();

  try
  {
    Calc();
  }
  catch(ParserError &e)
  {
    // Only erros raised during the initialization will end up here
    // expression related errors are treated in Calc()
    console() << _T("Initialization error:  ") << e.GetMsg() << endl;
  }
  catch(std::runtime_error &)
  {
    console() << _T("aborting...") << endl;
  }
  
#ifdef MUP_LEAKAGE_REPORT  
  IToken::LeakageReport();  
#endif

  return 0;
}
