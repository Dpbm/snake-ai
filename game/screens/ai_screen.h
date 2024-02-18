#pragma once

#include "screens.h"
#include "../player.h"
#include "../food.h"
#include "../../machine/machine.h"
#include "../../machine/layer.h"
#include "../../matrix/matrix.h"

using Screens::Screen;
using Players::Player;
using Foods::Food;
using Machine::NN;
using Layers::Layer;
using Matrices::Matrix;

namespace GameAIScreen{
  class AIScreen: public Screen{
    public:
      AIScreen();
      void execute(SDL_Renderer* render, bool& game_loop);
      Screen* key_event(const SDL_Keycode& key);
      ~AIScreen();
    private:
      unsigned int max_score = 10;
      Player* player = new Player(1, this->max_score);
      Food* food = new Food;
      bool debug = false;
      NN* nn = new NN; 
      Layer* input_layer = new Layer(7, true);
      Matrix<double>* input_data = new Matrix<double>(7, 1);
  };
};
