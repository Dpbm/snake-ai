#pragma once

#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include "../board.h"

using Game::Board;

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
      SDL_Color text_color{ 255, 255, 255 };
      uint16_t left_padding = 0;

      void render_board(Board *board);
  };
};
