#pragma once

#include <cstdint>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include "screens.h"
#include "../board.h"
#include "../players/qubo_player.h"

using Screens::Screen;
using Game::Board;
using Players::QuboPlayer;

namespace Screens{
  class QuboScreen: public Screen{
    public:
      QuboScreen(SDL_Renderer* render);
      ~QuboScreen();
      void execute(bool& game_loop);
      Screen* key_event(const SDL_Keycode& key);
      void close_event();     

    private:
      uint8_t board_w = 45;
      uint8_t board_h = 30;
      Board board{board_w, board_h};  
     
      bool finished_game = false;

      uint16_t max_score = 1000;
      QuboPlayer* player = new QuboPlayer(board_w, board_h);

      TTF_Font* font = TTF_OpenFont("./assets/pressstart.ttf", 20);
      TTF_Font* title_font = TTF_OpenFont("./assets/pressstart.ttf", 40);
      
      SDL_Rect score_text_shape;
      SDL_Rect score_shape;
      SDL_Texture* score_text_texture = nullptr;
      SDL_Texture* score_texture = nullptr;
      
      void reset();
  };
};
