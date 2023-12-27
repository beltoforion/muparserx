#!/bin/bash -eu

mkdir build
cd build
cmake ../
make

# Copy all fuzzer executables to $OUT/
$CXX $CFLAGS $LIB_FUZZING_ENGINE \
  $SRC/muparserx/.clusterfuzzlite/parser_fuzzer.cpp \
  -stdlib=libc++ -std=c++17 \
  -o $OUT/parser_fuzzer \
  -I$SRC/muparserx/parser \
  $SRC/muparserx/build/libmuparserx.a
