#pragma once

#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>

namespace Screens{
  class Screen{
    public:
      virtual void execute(SDL_Renderer* render, bool& game_loop);
      virtual Screen* key_event(const SDL_Keycode& key);
      virtual ~Screen();
  };
};
