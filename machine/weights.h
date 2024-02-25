#pragma once

#include <iostream>
#include "../genetic/gene.h"
#include "../matrix/matrix.h"

using std::string;
using Matrices::Matrix;
using Genes::Gene;

namespace NNWeights {
  
  class Weights{
    public:
      Weights(unsigned int first_layer_size, unsigned int second_layer_size);
      void load_weights(Matrix<Gene>* weights);
      Matrix<Gene>* get_weights();
      ~Weights();
      unsigned int get_width();
      unsigned int get_height();
      void save_weights(string filename);

    private:
      unsigned int width, height;
      Matrix<Gene> *weights;

  };
};
