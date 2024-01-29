#pragma once

#include "../matrix/matrix.h"

using Matrices::Matrix;

namespace Layers{
  class Layer{
    public:
      Layer(unsigned int size);
      Layer(Matrix *values);
      Matrix* get_values();
      unsigned int get_size() const;
      ~Layer();
    private:
      unsigned int size;
      Matrix *values;
  };
  
};
