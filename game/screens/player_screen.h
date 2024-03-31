#pragma once

#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <cstdint>
#include "screens.h"
#include "../players/player.h"
#include "../board.h"
#include "../../helpers/constants.h"

using Players::Player;
using Game::Board;


namespace Screens{

  class PlayerScreen : public Screen{
    public:
      PlayerScreen(SDL_Renderer* render);
      void execute(SDL_Renderer* render, bool& game_loop);
      Screen* key_event(const SDL_Keycode& key);
      ~PlayerScreen();
      void close_event();
    
    private:
      SDL_Renderer *render = nullptr;
    
      uint16_t left_padding = 10 * SQUARE_SIDE;
      uint8_t board_w = 45;
      uint8_t board_h = 30;
      Board board{board_w, board_h};  

      bool finished_game = false;

      uint16_t max_score = 100;
      uint8_t score_step = 10;
      Player* player = new Player{score_step, max_score, board_w, board_h};
      TTF_Font* font = TTF_OpenFont("./assets/pressstart.ttf", 20);
      TTF_Font* title_font = TTF_OpenFont("./assets/pressstart.ttf", 40);
      SDL_Color text_color{ 255, 255, 255 };
      SDL_Rect score_text_shape;
      SDL_Rect score_shape;
      SDL_Texture* score_text_texture = nullptr;
      SDL_Texture* score_texture = nullptr;
  
      void reset();
  };
};
