#pragma once

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <cstdint>
#include "../helpers/constants.h"

namespace Foods {
  class Food{
    public:
      Food();
      int16_t get_x();
      int16_t get_y();
      void render(SDL_Renderer* render);
      ~Food();
      void update_position();
      void set_position(uint16_t x, uint16_t y);

    private:
      SDL_Rect *shape = new SDL_Rect{0, 0, FOOD_W, FOOD_H}; 
      double rendered = false;
  };
};
