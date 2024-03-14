#pragma once

#include <cstdint>
#include "../genetic/chromosome.h"
#include "../matrix/matrix.h"
#include "player.h"

using Chromosomes::Chromosome;
using Matrices::Matrix;
using Players::Player;

namespace Players{
  class AIPlayer : Player {
    public:
      AIPlayer();
      ~AIPlayer();
      void setup_choromosome(unsigned int chromosome_size);
      Chromosome* get_chromosome();
      Matrix* get_genes_matrix(unsigned int w, unsigned int h);
      void update_input_data(Matrix* input_data, uint16_t px, uint16_t py, uint16_t fx, uint16_t fy);

    private:
      Chromosome* chromosome = nullptr;
  };
};
