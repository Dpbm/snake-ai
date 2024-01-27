#pragma once

namespace Utils {
  unsigned int get_random_pos(unsigned int max_range, unsigned int factor);
  double random(int start, int end);
  bool passed_debounce_time(int last_tick);
}
