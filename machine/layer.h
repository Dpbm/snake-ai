#pragma once

#include "../matrix/matrix.h"

using Matrices::Matrix;

namespace Layers{
  class Layer{
    public:
      Layer(unsigned int size, bool input=false);
      Layer(Matrix *values, bool input=false);
      Matrix* get_values();
      unsigned int get_size() const;
      ~Layer();
      void set_activation_function(double (*activation)(double));
      void activate_neurons();
    private:
      unsigned int size;
      bool input = false;
      Matrix *values;
      double (*activation)(double);
  };
  
};
