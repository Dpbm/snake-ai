#pragma once

#include <iostream>
#include <vector>
#include "layer.h"
#include "weights.h"
#include "../matrix/matrix.h"

using Machine::Layer;
using Machine::Weights;
using std::vector;
using std::string;

namespace Machine {
  class NN{  
    public:
      void add_layer(unsigned int size);
      void add_layer(Layer* layer);
      vector<Layer*> get_layers();
      vector<Weights*> get_weights();
      Layer* get_layer(unsigned int i);
      Weights* get_weight(unsigned int i);
      unsigned int get_total_layers();
      unsigned int get_total_weights();
      void save_weights(string path);
      ~NN();
      void feedforward();
      Layer* get_output_layer();
      Layer* get_input_layer();
      void load_weights(vector<Matrix*> new_weights);

    private:
      vector<Layer*> layers;
      vector<Weights*> weights;
      unsigned int total_layers = 0;
      unsigned int total_weights = 0;
      void add_weight();
      void save_arch(string filename);
  };
};
