#pragma once

#include <iostream>
#include <vector>
#include "layer.h"
#include "weights.h"

using Layers::Layer;
using NNWeights::Weights;
using std::vector;
using std::string;

namespace Machine {
  class NN{  
    public:
      void add_layer(unsigned int size);
      void add_layer(Layer* layer);
      vector<Layer*>* get_layers();
      vector<Weights*>* get_weights();
      Layer* get_layer(unsigned int i);
      Weights* get_weight(unsigned int i);
      unsigned int get_total_layers();
      unsigned int get_total_weights();
      void save_weights(string filename);
      ~NN();

    private:
      vector<Layer*>* layers = new vector<Layer*>;
      vector<Weights*>* weights = new vector<Weights*>;
      unsigned int total_layers = 0;
      unsigned int total_weights = 0;
      void add_weight();
  };
};
