#pragma once


#include <cstdint>
#include "ai_player.h"
#include "../machine/machine.h"
#include "../machine/layer.h"
#include "../matrix/matrix.h"
#include "../game/player.h"

using AIAgent::AIPlayer;
using Machine::NN;
using Layers::Layer;
using Matrices::Matrix;
using Players::Player;

namespace Populations {
  class Population{
    public:
      Population(uint8_t total);
      void load_genes_into_weights();
      void update_player_direction(Player* player);
      void update_actual_individual();
      bool is_the_last_individual();
      void reset_individual();
      void next_generation();
      ~Population();

    private:
      uint8_t total_individuals = 0;
      uint16_t total_weights = 0;

      NN* nn = new NN;   
      Layer* input_layer = new Layer(3, true);
      Matrix* input_data = new Matrix(3, 1);
      AIPlayer* individuals = nullptr;

      AIPlayer* actual_individual = nullptr;
      uint8_t indvidual_i = 0;

      void setup_nn();
      void get_new_direction(Player* player);
  };
};
