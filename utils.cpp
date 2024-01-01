#include <random>
#include "utils.h"
#include "constants.h"
#include <SDL2/SDL_timer.h>

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
  
  bool passed_debounce_time(int last_tick){
    return  SDL_GetTicks() - last_tick >= DEBOUNCE_TIME;
  }
}
