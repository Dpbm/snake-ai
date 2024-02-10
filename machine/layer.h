#pragma once

#include <iostream>
#include "../matrix/matrix.h"

using Matrices::Matrix;

namespace Layers{
  class Layer{
    public:
      Layer(unsigned int size, bool input);
      Layer(Matrix<double> *values, bool input);
      Matrix<double>* get_values();
      unsigned int get_size() const;
      ~Layer();
      void set_activation_function(double (*activation)(double));
      void activate_neurons();
      bool is_input();
      double (*get_activation_function())(double);
      void set_values(Matrix<double>* values);
    private:
      unsigned int size;
      bool input = false;
      Matrix<double> *values;
      double (*activation)(double);
  };
};
