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
      bool run_population();
      AIPlayer* get_individuals();
      void next_generation();
      int64_t get_best_fitness();
      uint8_t get_best_fitness_i();
      AIPlayer* get_best_player();
      AIPlayer* get_best_player_alive();
      uint32_t get_generation();
      void update_gen();
      ~Population();

    private:
      uint32_t generation = 1;
      uint32_t max_generation = 1000;
      uint8_t total_individuals = 0;
      AIPlayer* individuals = nullptr;

      vector<int64_t> fitness;

      uint8_t score_step;
      uint16_t max_score;

      void reset_individuals();
  };
};
