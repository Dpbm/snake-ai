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
      void execute(SDL_Renderer* render, bool& game_loop);
      Screen* key_event(const SDL_Keycode& key);
      void close_event();     

    private:
      uint16_t left_padding = 12 * SQUARE_SIDE;
      uint8_t board_w = 30;
      uint8_t board_h = 30;

      uint8_t gen_time = 30; //in seconds
      uint8_t actual_time = 0;
      uint32_t last_tick = 0;

      Population population{2000, board_w, board_h, 20};

      SDL_Renderer* render;
      TTF_Font* font = TTF_OpenFont("./assets/pressstart.ttf", 20);
      SDL_Color text_color{ 255, 255, 255 };
     
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
      
      SDL_Rect fitness_text_shape;
      SDL_Rect fitness_shape;
      SDL_Texture* fitness_text_texture = nullptr;
      SDL_Texture* fitness_texture = nullptr;
      
      SDL_Rect timer_text_shape;
      SDL_Rect timer_shape;
      SDL_Texture* timer_text_texture = nullptr;
      SDL_Texture* timer_texture = nullptr;
  };
};
