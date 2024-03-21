#pragma once

#include <ctime>
#include <vector>
#include <cstdint>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include "screens.h"
#include "../players/ai_player.h"
#include "../../genetic/population.h"

using std::vector;
using Screens::Screen;
using Players::AIPlayer;
using Populations::Population;

namespace GameAIScreen{
  class AIScreen: public Screen{
    public:
      AIScreen(SDL_Renderer* render);
      ~AIScreen();
      void execute(SDL_Renderer* render, bool& game_loop);
      Screen* key_event(const SDL_Keycode& key);
      
    private:
      uint8_t max_score = 100;
      uint8_t population_size = 200;

      uint32_t start_tick = 0;

      Population* population = new Population(population_size, 1, max_score);
      AIPlayer* player = nullptr;
     
      SDL_Renderer* render;
      TTF_Font* font = TTF_OpenFont("./assets/pressstart.ttf", 20);
      SDL_Color text_color{ 255, 255, 255 };
  
      SDL_Rect score_text_shape;
      SDL_Rect score_shape;
      SDL_Texture* score_text_texture;
      SDL_Texture* score_texture;

      SDL_Rect generation_text_shape;
      SDL_Rect generation_shape;
      SDL_Texture* generation_text_texture;
      SDL_Texture* generation_texture;
      
      SDL_Rect best_individual_text_shape;
      SDL_Rect best_individual_shape;
      SDL_Texture* best_individual_text_texture;
      SDL_Texture* best_individual_texture;
      
      SDL_Rect timer_text_shape;
      SDL_Rect timer_shape;
      SDL_Texture* timer_text_texture;
      SDL_Texture* timer_texture;
      
      SDL_Rect screen_separator{LEFT_WALL, 0, 1, HEIGHT};
      void create_text();
      void start_new_game();
      void randomize_player_direction();
      void clear_textures();
  };
};
