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
      void next_generation();
      void add_points(int16_t points);
      void add_distance(uint16_t distance);
      ~Population();

    private:
      uint8_t total_individuals = 0;
      uint16_t total_weights = 0;
      uint16_t* distances;
      int16_t* points;


      NN* nn = new NN;   
      Layer* input_layer = new Layer(2, true);
      Matrix* input_data = new Matrix(2, 1);
      AIPlayer* individuals;
      uint8_t actual_individual = 0;

      void setup_nn();
      void get_nn_total_weights();
      void get_new_direction(Player* player);
  };
};
