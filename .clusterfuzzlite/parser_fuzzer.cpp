#include "mpParser.h"
#include <string>

using namespace mup;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string fuzz_input(reinterpret_cast<const char *>(data), size);
  ParserX p;

  try {
    p.SetExpr(fuzz_input);
    p.Eval();
  } catch (...) {
  }

  return 0;
}
