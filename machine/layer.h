#pragma once

#include <iostream>
#include <type_traits>
#include "../matrix/matrix.h"

using std::is_floating_point;
using std::is_integral;
using std::enable_if;
using Matrices::Matrix;
using Matrices::MatrixOfNumbersTemplate;

namespace Layers{
    
  template <typename T> using MatrixLayerTemplate = MatrixOfNumbersTemplate<T>;

  template <typename T>
  class Layer{
    public:
      Layer(unsigned int size, bool input);
      Layer(Matrix<MatrixLayerTemplate<T>> *values, bool input);
      Matrix<MatrixLayerTemplate<T>>* get_values();
      unsigned int get_size() const;
      ~Layer();
      void set_activation_function(double (*activation)(double));
      void activate_neurons();
      bool is_input();
      double (*get_activation_function())(double);
      void set_values(Matrix<MatrixLayerTemplate<T>>* values);
    private:
      unsigned int size;
      bool input = false;
      Matrix<MatrixLayerTemplate<T>> *values;
      double (*activation)(double);
  };
  
};
