#ifndef MU_MATRIX_ERROR_H
#define MU_MATRIX_ERROR_H

#include <stdexcept>
#include <string>

MUP_NAMESPACE_START

  class MatrixError : public std::runtime_error
  {
  public:
    explicit MatrixError(const std::string &sMsg)
        :std::runtime_error(sMsg)
    {}
  };

MUP_NAMESPACE_END

#endif