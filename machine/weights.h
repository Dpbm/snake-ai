#pragma once

#include <iostream>
#include "../matrix/matrix.h"

using Matrices::Matrix;
using Matrices::MatrixTemplate;
using std::string;

namespace NNWeights {

  template <typename T>
  class Weights{
    public:
      Weights(unsigned int first_layer_size, unsigned int second_layer_size);
      void load_weights(Matrix<MatrixTemplate<T>>* weights);
      Matrix<MatrixTemplate<T>>* get_weights();
      ~Weights();
      unsigned int get_width();
      unsigned int get_height();
      void save_weights(string filename);

    private:
      unsigned int width, height;
      Matrix<MatrixTemplate<T>>*weights;
      void clear_pointers();

  };
};
