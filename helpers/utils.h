#pragma once

#include <cstdint>
#include <iostream>
#include <vector>
#include "../matrix/matrix.h"

using std::vector;
using std::string;
using Matrices::Matrix;

namespace Utils {
  uint16_t get_random_x(uint16_t factor);
  uint16_t get_random_y(uint16_t factor);
  double random(double start, double end);
  uint64_t random_int(uint64_t start, uint64_t end);
  bool passed_debounce_time(uint32_t last_tick);
  void append_to_file(string filename, string data);
  void create_file(string filename, string data);
  vector<Matrix*> parse_weigths_file(string filename);
}
