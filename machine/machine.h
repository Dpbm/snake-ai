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
      vector<Layer*>* get_layers();
      Layer* get_layer(unsigned int i);
      unsigned int get_total_layers();
      ~NN();

    private:
      vector<Layer*>* layers = new vector<Layer*>;
      unsigned int total_layers = 0;
      
  };
};
