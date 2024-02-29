#include <iostream>
#include <random>
#include <fstream>
#include <SDL2/SDL_timer.h>
#include "utils.h"
#include "constants.h"

using std::ofstream;
using std::string;
using std::ios;

namespace Utils {
  double random(int start, int end){
    std::random_device device;
    std::mt19937 eng(device());
    std::uniform_real_distribution<> distr(start, end);
    
    return distr(eng);
  }
  
  unsigned int random_int(int start, int end){
    std::random_device device;
    std::mt19937 eng(device());
    std::uniform_int_distribution<> distr(start, end);
    
    return distr(eng);
  }

  unsigned int get_random_x(unsigned int factor){
    unsigned int rand = Utils::random_int(LEFT_WALL, WIDTH);
    return rand-(rand%factor);
  }
  
  unsigned int get_random_y(unsigned int factor){
    unsigned int rand = Utils::random_int(0, HEIGHT);
    return rand-(rand%factor);
  }

  void append_to_file(string filename, string data){
    ofstream file;
    file.open(filename, ios::app);

    if(!file){
      Utils::create_file(filename, data);
      return;
    }

    file << data;
    file.close();
  }

  void create_file(string filename, string data){
    ofstream file(filename);

    if(file.is_open()){
      file << data;
      file.close();
    }
  }

  bool passed_debounce_time(int last_tick){
    return SDL_GetTicks() - last_tick >= DEBOUNCE_TIME;
  }

}
