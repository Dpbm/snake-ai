#pragma once

#include <iostream>

using std::string;

namespace Utils {
  unsigned int get_random_pos(unsigned int max_range, unsigned int factor);
  double random(int start, int end);
  bool passed_debounce_time(int last_tick);
  void append_to_file(string filename, string data);
  void create_file(string filename, string data);
}
