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
using Layers::Layer;


namespace Players{
  enum Directions{UP=0, DOWN=1, LEFT=2, RIGHT=3};
  
  class AIPlayer : public Player {
    public:
      AIPlayer();
      ~AIPlayer();
      Chromosome* get_chromosome();
      Matrix* get_genes_matrix(unsigned int w, unsigned int h);
      void update_input_data(int16_t fx, int16_t fy);
      Directions get_new_direction();
      void setup_agent(uint8_t score_step, uint16_t max_score); 
      void randomize_direction();
      bool is_trying_invalid_direction(Directions dir);
      void update_direction(Directions dir);

    private:
      Chromosome* chromosome = nullptr;
      Directions direction = UP;   

      NN* nn = new NN;   
      Layer* input_layer = new Layer(7, true);
      Matrix* input_data = new Matrix(7, 1);
  
  };
};
