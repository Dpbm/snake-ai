#pragma once

#include <cstdint>
#include "../../genetic/chromosome.h"
#include "../../matrix/matrix.h"
#include "../../machine/machine.h"
#include "../../machine/layer.h"
#include "player.h"

using Chromosomes::Chromosome;
using Matrices::Matrix;
using Machine::NN;
using Machine::Layer;

namespace Players{
  
  class AIPlayer : public Player {
    public:
      AIPlayer(uint8_t score_step, uint8_t board_w, uint8_t board_h);
      ~AIPlayer();
  
      void load_genes_into_weights();

    private:
      Chromosome* chromosome = nullptr;
      NN* nn = new NN;   
      Layer* input_layer = new Layer(3, true);
      Matrix* input_data = new Matrix(3, 1);

      void setup_nn();
      void setup_chromosome();

    


  
  };
};
