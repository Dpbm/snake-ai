#pragma once

#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>

namespace Screens{
  class Screen{
    public:
      Screen(SDL_Renderer* render);
      virtual void execute(bool& game_loop);
      virtual Screen* key_event(const SDL_Keycode& key);
      virtual ~Screen();
      virtual void close_event();

    protected:
      SDL_Renderer* render = nullptr;
  };
};
