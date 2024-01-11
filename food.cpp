#include "food.h"
#include "helpers/constants.h"
#include "helpers/utils.h"

namespace Foods {
  unsigned int x, y;
  
  Food::Food(){
    this->x = Utils::get_random_pos(WIDTH, FOOD_W);  
    this->y = Utils::get_random_pos(HEIGHT, FOOD_H);
  }
  
  unsigned int Food::get_x(){
    return this->x;
  }
  
  unsigned int Food::get_y(){
    return this->y;
  }
}
