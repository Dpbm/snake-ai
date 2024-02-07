#pragma once

#include "../matrix/matrix.h"

using Matrices::Matrix;
using Matrices::MatrixTemplate;

namespace Layers{
  template <typename T>
  class Layer{
    public:
      Layer(unsigned int size, bool input);
      Layer(Matrix<MatrixTemplate<T>> *values, bool input);
      Matrix<MatrixTemplate<T>>* get_values();
      unsigned int get_size() const;
      ~Layer();
      void set_activation_function(double (*activation)(double));
      void activate_neurons();
      bool is_input();
      double (*get_activation_function())(double);
      void set_values(Matrix<MatrixTemplate<T>>* values);
    private:
      unsigned int size;
      bool input = false;
      Matrix<MatrixTemplate<T>> *values;
      double (*activation)(double);
  };
  
};
