#!/bin/sh
TARGET_MAIN=$1
echo "Using 'main' as: $TARGET_MAIN"
cmake -DTARGET_MAIN="$TARGET_MAIN" -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang -S . -B build
cmake --build build
