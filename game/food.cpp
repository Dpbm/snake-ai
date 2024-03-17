#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <cstdint>
#include "food.h"
#include "../helpers/constants.h"
#include "../helpers/utils.h"

using Utils::get_random_x;
using Utils::get_random_y;

namespace Foods {
  SDL_Rect *shape; 
  double rendered;

  Food::Food(){
    this->update_position();
  }
  
  int16_t Food::get_x(){
    return this->shape->x;
  }
  
  int16_t Food::get_y(){
    return this->shape->y;
  }

  void Food::set_position(uint16_t x, uint16_t y){
    this->shape->x = x;
    this->shape->y = y;
  }

  void Food::render(SDL_Renderer* render){
    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    SDL_RenderFillRect(render, this->shape);
    SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
  }

  Food::~Food(){
    delete this->shape;
  }

  void Food::update_position(){
    this->shape->x = get_random_x(FOOD_W);  
    this->shape->y = get_random_y(FOOD_H);
  }
}
