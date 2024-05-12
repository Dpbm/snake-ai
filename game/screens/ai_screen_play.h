#pragma once

#include <cstdint>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include "screens.h"
#include "../board.h"
#include "../players/ai_player.h"

using Screens::Screen;
using Game::Board;
using Players::AIPlayer;

namespace Screens{
  class AIPlayScreen: public Screen{
    public:
      AIPlayScreen(SDL_Renderer* render);
      ~AIPlayScreen();
      void execute(bool& game_loop);
      Screen* key_event(const SDL_Keycode& key);
      void close_event();     

    private:
      uint8_t board_w = 43;
      uint8_t board_h = 30;
      Board board{board_w, board_h};  
      
      uint16_t max_score = 1000;
      AIPlayer* player = nullptr;

  };
};
