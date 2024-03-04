#pragma once

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include "../helpers/constants.h"

namespace Foods {
  class Food{
    public:
      Food();
      unsigned int get_x();
      unsigned int get_y();
      void render(SDL_Renderer* render);
      ~Food();
      void update_position();
      void set_position(unsigned int x, unsigned int y);

    private:
      SDL_Rect *shape = new SDL_Rect{0, 0, FOOD_W, FOOD_H}; 
      double rendered = false;
  };
};
