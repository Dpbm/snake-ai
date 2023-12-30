#include <algorithm>
#include <random>
#include "utils.h"

namespace Utils {
  unsigned int random(unsigned int start,  unsigned int end){
    std::random_device device;
    std::mt19937 eng(device());
    std::uniform_int_distribution<> distr(start, end);
    
    return distr(eng);
  }
  
  unsigned int get_random_pos(unsigned int max_range, unsigned int factor){
    unsigned int rand = Utils::random(0, max_range);
    return rand-(rand%factor);
  }

}
