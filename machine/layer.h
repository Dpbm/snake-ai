#pragma once

#include "../matrix/matrix.h"

using Matrices::Matrix;

namespace Layers{
  class Layer{
    public:
      Layer(unsigned int size, bool input);
      Layer(Matrix *values, bool input);
      Matrix* get_values();
      unsigned int get_size() const;
      ~Layer();
      void set_activation_function(double (*activation)(double));
      void activate_neurons();
      bool is_input();
      double (*get_activation_function())(double);
    private:
      unsigned int size;
      bool input = false;
      Matrix *values;
      double (*activation)(double);
  };
  
};
