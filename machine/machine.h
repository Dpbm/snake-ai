#pragma once

#include <iostream>
#include <vector>
#include "layer.h"

using Layers::Layer;
using std::vector;

namespace Machine {

  class NN{
  
    public:
      void add_layer(unsigned int size);
      void add_layer(Layer* layer);

    private:
      vector<Layer*>* layers = new vector<Layer*>;
  };
};
