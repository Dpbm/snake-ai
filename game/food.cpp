#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include "food.h"
#include "../helpers/constants.h"
#include "../helpers/utils.h"

using Utils::get_random_pos;

namespace Foods {
  unsigned int x, y;
  SDL_Rect *shape; 
  double rendered;

  Food::Food(){
    this->update_position();
  }
  
  unsigned int Food::get_x(){
    return this->x;
  }
  
  unsigned int Food::get_y(){
    return this->y;
  }

  void Food::render(SDL_Renderer* render){
    this->shape->x = this->x;
    this->shape->y = this->y;
    this->shape->h = FOOD_H;
    this->shape->w = FOOD_W;
    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    SDL_RenderFillRect(render, this->shape);
    SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
  }

  Food::~Food(){
    delete this->shape;
  }

  void Food::update_position(){
    this->x = get_random_pos(WIDTH, FOOD_W);  
    this->y = get_random_pos(HEIGHT, FOOD_H);
  }
}
