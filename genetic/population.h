#pragma once


#include <cstdint>
#include <vector>
#include "../machine/machine.h"
#include "../machine/layer.h"
#include "../matrix/matrix.h"
#include "../game/players/ai_player.h"

using std::vector;
using Machine::NN;
using Layers::Layer;
using Matrices::Matrix;
using Players::AIPlayer;
using Players::Directions;

namespace Populations {
  class Population{
    public:
      Population(uint8_t total, uint8_t score_step, uint16_t max_score);
      // void update_actual_individual();
      // bool is_the_last_individual();
      // AIPlayer* get_actual_individual();
      // void reset_agents();
      // void update_direction_data(Directions dir);
      // void update_distance_data(int16_t fx, int16_t fy);
      // void update_points_data();
      void run_population(int16_t fx, int16_t fy);
      ~Population();

    private:
      // int64_t* fitness;
      // vector<uint16_t> distances;      
  
      uint8_t total_individuals = 0;
      AIPlayer* individuals = nullptr;
      // AIPlayer* actual_individual = nullptr;
      // uint8_t indvidual_i = 0;

      uint8_t score_step;
      uint16_t max_score;
  };
};
