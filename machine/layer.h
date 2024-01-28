#pragma once

#include "../matrix/matrix.h"

using Matrices::Matrix;

namespace Layers{

  struct Layer{
    virtual void set_node_values(Matrix *values);
  };

  class InputLayer: Layer{
    public:
      InputLayer(unsigned int width, unsigned int height);
      void set_node_values(Matrix *values);
      ~InputLayer();
    private:
      unsigned int width, height;
      Matrix *values;
  };
  
};
