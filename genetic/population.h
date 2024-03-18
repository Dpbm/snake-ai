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
      bool run_population(int16_t fx, int16_t fy);
      AIPlayer* get_individuals();
      void next_generation();
      ~Population();

    private:
      uint8_t total_individuals = 0;
      AIPlayer* individuals = nullptr;

      vector<int64_t> fitness;

      uint8_t score_step;
      uint16_t max_score;

      void reset_individuals();
  };
};
