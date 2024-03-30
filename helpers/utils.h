#pragma once

#include <cstdint>
#include <iostream>
#include <vector>
#include "../matrix/matrix.h"

using std::vector;
using std::string;
using Matrices::Matrix;

namespace Utils {
  typedef struct vec2{
    int16_t x,y;
  }vec2;

  double random(double start, double end);
  int16_t random_int(uint8_t start, uint8_t end);
  bool passed_debounce_time(uint32_t last_tick);
  void append_to_file(string filename, string data);
  void create_file(string filename, string data);
  vector<Matrix*> parse_weigths_file(string filename);
}
