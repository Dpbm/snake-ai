#pragma once

#include <cstdint>
#include "../genetic/chromosome.h"
#include "../matrix/matrix.h"
#include "../machine/machine.h"
#include "../machine/layer.h"
#include "player.h"

using Chromosomes::Chromosome;
using Matrices::Matrix;
using Machine::NN;
using Layers::Layer;

namespace Players{
  class AIPlayer : public Player {
    public:
      AIPlayer();
      ~AIPlayer();
      Chromosome* get_chromosome();
      Matrix* get_genes_matrix(unsigned int w, unsigned int h);
      void update_input_data(uint16_t fx, uint16_t fy);
      void get_new_direction();
      void setup_agent(uint8_t score_step, uint16_t max_score); 
      void randomize_direction();

    private:
      Chromosome* chromosome = nullptr;
      
      NN* nn = new NN;   
      Layer* input_layer = new Layer(3, true);
      Matrix* input_data = new Matrix(3, 1);
  
  };
};
