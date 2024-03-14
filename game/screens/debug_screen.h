#pragma once

#include "./screens.h"
#include "../player.h"
#include "../food.h"
#include "ai_screen.h"
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include "../../machine/machine.h"
#include "../../machine/layer.h"
#include "../../matrix/matrix.h"

using Machine::NN;
using Layers::Layer;
using Matrices::Matrix;
using Screens::Screen;
using Players::Player;
using Foods::Food;

namespace GameDebugScreen {
  class DebugScreen : public Screen{
    public:
      DebugScreen(SDL_Renderer* render);
      void execute(SDL_Renderer* render, bool& game_loop);
      Screen* key_event(const SDL_Keycode& key);
      ~DebugScreen();
      void update_input_data(uint16_t px, uint16_t py, uint16_t fx, uint16_t fy);
      void update_player_direction();
    
  private:
      Player* player = new Player(1, 100);
      Food food;
      NN* nn = new NN;   
      Layer* input_layer = new Layer(3, true);
      Matrix* input_data = new Matrix(3, 1);
      void get_new_direction();
      void reset_weights();
  };
};
