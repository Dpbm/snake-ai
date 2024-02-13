#pragma once

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

namespace Foods {
  class Food{
    public:
      Food();
      unsigned int get_x();
      unsigned int get_y();
      void render(SDL_Renderer* render);
      ~Food();
      void update_position();

    private:
      unsigned int x, y;
      SDL_Rect *shape = new SDL_Rect; 
      double rendered = false;
  };
};
