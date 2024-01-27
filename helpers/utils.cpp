#include <random>
#include "utils.h"

namespace Utils {
  double random(int start, int end){
    std::random_device device;
    std::mt19937 eng(device());
    std::uniform_real_distribution<> distr(start, end);
    
    return distr(eng);
  }
  
  unsigned int get_random_pos(unsigned int max_range, unsigned int factor){
    unsigned int rand = Utils::random(0, max_range);
    return rand-(rand%factor);
  }
}
