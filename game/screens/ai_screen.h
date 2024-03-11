#pragma once

#include <vector>
#include <cstdint>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include "screens.h"
#include "../player.h"
#include "../food.h"
#include "../../genetic/population.h"

using std::vector;
using Screens::Screen;
using Players::Player;
using Foods::Food;
using Populations::Population;

namespace GameAIScreen{
  class AIScreen: public Screen{
    public:
      AIScreen(SDL_Renderer* render);
      void execute(SDL_Renderer* render, bool& game_loop);
      void randomize_player_direction();
      void reset(SDL_Renderer* render);
      Screen* key_event(const SDL_Keycode& key);
      ~AIScreen();

    private:
      constexpr static uint8_t max_score = 10;
      constexpr static uint8_t total_individuals = 4;
      uint8_t generation = 1;
      uint8_t individual = 1;
      uint8_t best_individual = 1;
      uint8_t best_pontuation = 0;
      uint16_t best_food_distance = (uint16_t)1000000;
      Population* population = new Population(total_individuals);
      Player* player = new Player(1, max_score);
      uint16_t fx,fy;
      Food food;
      int8_t points[total_individuals];
      
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
      
      SDL_Rect individual_text_shape;
      SDL_Rect individual_shape;
      SDL_Texture* individual_text_texture;
      SDL_Texture* individual_texture;
      
      SDL_Rect best_individual_text_shape;
      SDL_Rect best_individual_shape;
      SDL_Texture* best_individual_text_texture;
      SDL_Texture* best_individual_texture;
      
      SDL_Rect best_pontuation_text_shape;
      SDL_Rect best_pontuation_shape;
      SDL_Texture* best_pontuation_text_texture;
      SDL_Texture* best_pontuation_texture;
      
      SDL_Rect screen_separator{LEFT_WALL, 0, 1, HEIGHT};
      void create_text(SDL_Renderer* render);
      void update_best_individual_and_pontutaion_text(SDL_Renderer* render);
      void randomize_food_position();
      void get_food_distance();
  };
};
