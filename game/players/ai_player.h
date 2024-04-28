#pragma once

#include <cstdint>
#include "../../genetic/chromosome.h"
#include "../../matrix/matrix.h"
#include "../../machine/machine.h"
#include "../../machine/layer.h"
#include "../../helpers/utils.h"
#include "player.h"

using Chromosomes::Chromosome;
using Matrices::Matrix;
using Machine::NN;
using Machine::Layer;
using Utils::vec2;

namespace Players{
  
  class AIPlayer : public Player {
    public:
      AIPlayer(uint8_t board_w, uint8_t board_h);
      ~AIPlayer();
  
      void load_genes_into_weights();
      void update_input_data(const vec2& food, uint16_t w, uint16_t h);
      void compute_next_dir();
      void update_dir();

    private:
      Chromosome* chromosome = nullptr;
      NN* nn = new NN;   
      Layer* input_layer = new Layer(3, true);
      Matrix* input_data = new Matrix(3, 1);

      void setup_nn();
      void setup_chromosome();
  };
};
