#pragma once

#include <ctime>
#include <vector>
#include <cstdint>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include "screens.h"
#include "../board.h"
#include "../../helpers/constants.h"
#include "../players/ai_player.h"
#include "../../genetic/population.h"

using Screens::Screen;
using Game::Board;
using Players::AIPlayer;
using Genetic::Population;

namespace Screens{
  class AIScreen: public Screen{
    public:
      AIScreen(SDL_Renderer* render);
      ~AIScreen();
      void execute(bool& game_loop);
      Screen* key_event(const SDL_Keycode& key);
      void close_event();     

    private:
      uint8_t board_w = 43;
      uint8_t board_h = 30;

      uint8_t gen_time = 40; //in seconds
      uint32_t control_tick = 0;

      Population population{3000, board_w, board_h, 20};

      TTF_Font* font = TTF_OpenFont("./assets/pressstart.ttf", 20);
      TTF_Font* tiny_font = TTF_OpenFont("./assets/pressstart.ttf", 12);
     
      SDL_Rect score_text_shape;
      SDL_Rect score_shape;
      SDL_Texture* score_text_texture = nullptr;
      SDL_Texture* score_texture = nullptr;

      SDL_Rect gen_text_shape;
      SDL_Rect gen_shape;
      SDL_Texture* gen_text_texture = nullptr;
      SDL_Texture* gen_texture = nullptr;
      
      SDL_Rect alive_text_shape;
      SDL_Rect alive_shape;
      SDL_Texture* alive_text_texture = nullptr;
      SDL_Texture* alive_texture = nullptr;
      
      SDL_Rect win_text_shape;
      SDL_Rect win_shape;
      SDL_Texture* win_text_texture = nullptr;
      SDL_Texture* win_texture = nullptr;
      
      SDL_Rect fitness_text_shape;
      SDL_Rect fitness_shape;
      SDL_Texture* fitness_text_texture = nullptr;
      SDL_Texture* fitness_texture = nullptr;
      
      SDL_Rect timer_text_shape;
      SDL_Rect timer_shape;
      SDL_Texture* timer_text_texture = nullptr;
      SDL_Texture* timer_texture = nullptr;
 
      SDL_Rect weights_text_shape;
      SDL_Texture* weights_text_texture = nullptr;
      
      SDL_Rect return_text_shape;
      SDL_Texture* return_text_texture = nullptr;

      void save_weights();
  };
};
