#pragma once

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include "screens.h"
#include "../player.h"
#include "../food.h"
#include "../../machine/machine.h"
#include "../../machine/layer.h"
#include "../../matrix/matrix.h"
#include "../../genetic/chromosome.h"

using Screens::Screen;
using Players::Player;
using Foods::Food;
using Machine::NN;
using Layers::Layer;
using Matrices::Matrix;
using Chromosomes::Chromosome;

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
      constexpr static unsigned int max_score = 10;
      constexpr static unsigned int total_individuals = 3;
      unsigned int generation = 1;
      unsigned int individual = 1;
      unsigned int best_individual = 1;
      unsigned int best_pontuation = 0;
      int points[total_individuals];
      Chromosome* population = new Chromosome[total_individuals];
      Player* player = new Player(1, max_score);
      Food food;
      bool debug = false;
     
      NN* nn = new NN;   
      Layer* input_layer = new Layer(5, true);
      Matrix* input_data = new Matrix(5, 1);
      
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
      void load_genes_into_nn();
  };
};
