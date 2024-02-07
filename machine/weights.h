#pragma once

#include <iostream>
#include <type_traits>
#include "../matrix/matrix.h"

using std::is_floating_point;
using std::is_integral;
using std::enable_if;
using std::string;
using Matrices::Matrix;

namespace NNWeights {
  
    template <typename T, 
            typename enable_if<is_floating_point<T>::value || 
                               is_integral<T>::value || 
                               is_same<T, Gene>::value>::type* = nullptr> 
    using MatrixWeightsTemplate = T;

  template <typename T>
  class Weights{
    public:
      Weights(unsigned int first_layer_size, unsigned int second_layer_size);
      void load_weights(Matrix<MatrixWeightsTemplate<T>>* weights);
      Matrix<MatrixWeightsTemplate<T>>* get_weights();
      ~Weights();
      unsigned int get_width();
      unsigned int get_height();
      void save_weights(string filename);

    private:
      unsigned int width, height;
      Matrix<MatrixWeightsTemplate<T>>*weights;
      void clear_pointers();

  };
};
