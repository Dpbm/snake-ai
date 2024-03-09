#pragma once

#include "chromosome.h"
#include "../matrix/matrix.h"

using Chromosomes::Chromosome;
using Matrices::Matrix;

namespace AIAgent{
  class AIPlayer{
    public:
      AIPlayer();
      ~AIPlayer();
      void setup_choromosome(unsigned int chromosome_size);
      Chromosome* get_chromosome();
      Matrix* get_genes_matrix(unsigned int w, unsigned int h);

    private:
      Chromosome* chromosome = nullptr;
  };
};
