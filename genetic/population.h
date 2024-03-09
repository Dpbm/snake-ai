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
      void update_input_data(uint16_t px, uint16_t py, uint16_t fx, uint16_t fy);
      uint8_t get_actual_individual();
      void reset_individual();
      ~Population();

    private:
      uint16_t total_weights = 0;

      NN* nn = new NN;   
      Layer* input_layer = new Layer(1, true);
      Matrix* input_data = new Matrix(1, 1);
      AIPlayer* individuals;
      uint8_t actual_individual = 0;
      
      void setup_nn();
      void get_nn_total_weights();
      void get_new_direction(Player* player);
  };
};
