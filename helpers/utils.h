#pragma once

#include <cstdint>
#include <iostream>
#include <vector>

using std::vector;
using std::string;

namespace Utils {
  uint16_t get_random_x(uint16_t factor);
  uint16_t get_random_y(uint16_t factor);
  double random(double start, double end);
  unsigned int random_int(int start, int end);
  bool passed_debounce_time(int last_tick);
  void append_to_file(string filename, string data);
  void create_file(string filename, string data);
}
