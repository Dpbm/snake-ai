#pragma once


#include <cstdint>
#include "../machine/machine.h"
#include "../machine/layer.h"
#include "../matrix/matrix.h"
#include "../game/ai_player.h"

using Machine::NN;
using Layers::Layer;
using Matrices::Matrix;
using Players::AIPlayer;

namespace Populations {
  class Population{
    public:
      Population(uint8_t total);
      void update_actual_individual();
      bool is_the_last_individual();
      void reset_individual();
      void next_generation();
      ~Population();

    private:
      uint8_t total_individuals = 0;

      AIPlayer* individuals = nullptr;

      AIPlayer* actual_individual = nullptr;
      uint8_t indvidual_i = 0;

      void setup_nn();
  };
};
