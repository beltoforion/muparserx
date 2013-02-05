#include <limits>
#include "mpOprtPostfixCommon.h"

MUP_NAMESPACE_START

//-----------------------------------------------------------
//
// class OprtFact
//
//-----------------------------------------------------------

  OprtFact::OprtFact()
    :IOprtPostfix(_T("!"))
  {}

  //-----------------------------------------------------------
  void OprtFact::Eval(ptr_val_type& ret, const ptr_val_type *arg, int)
  {
      IValue *arg_1 = arg[0].Get();
      if (!arg_1->IsNonComplexScalar()) {
	  throw ParserError(ErrorContext(ecTYPE_CONFLICT_FUN, GetExprPos(),
					 GetIdent(), arg_1->GetType(), 'i', 1));
      }


      int input = arg_1->GetInteger();
      float_type input_long = static_cast<float_type>(input);

      if (input < 0) {
	  throw ParserError(ErrorContext(ecDOMAIN_ERROR, GetExprPos(),
					 GetIdent(), arg_1->GetType(), 'i', 1));
      }

      float_type result = 1;
      for (float_type i = 1.0; i <= input_long; i += 1.0) {
	  result *= i;

	  if ((result > std::numeric_limits<float_type>::max()) | (result < 1.0)) {
	      throw ParserError(ErrorContext(ecOVERFLOW, GetExprPos(),
					     GetIdent()));
	  }
      }

      *ret = result;
  }

  //-----------------------------------------------------------
  const char_type* OprtFact::GetDesc() const
  {
    return _T("x! - Returns factorial of a non-negative integer.");
  }

  //-----------------------------------------------------------
  IToken* OprtFact::Clone() const
  {
    return new OprtFact(*this);
  }

}
