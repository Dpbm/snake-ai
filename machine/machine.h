#pragma once

#include <iostream>
#include <vector>
#include "layer.h"
#include "weights.h"
#include "../matrix/matrix.h"

using Layers::Layer;
using Layers::MatrixLayerTemplate;
using NNWeights::Weights;
using NNWeights::MatrixWeightsTemplate;
using std::vector;
using std::string;

namespace Machine {
  template <typename L, typename W>
  class NN{  
    public:
      void add_layer(unsigned int size);
      void add_layer(Layer<MatrixLayerTemplate<L>>* layer);
      vector<Layer<MatrixLayerTemplate<L>>*>* get_layers();
      vector<Weights<MatrixWeightsTemplate<W>>*>* get_weights();
      Layer<MatrixLayerTemplate<L>>* get_layer(unsigned int i);
      Weights<MatrixWeightsTemplate<W>>* get_weight(unsigned int i);
      unsigned int get_total_layers();
      unsigned int get_total_weights();
      void save_weights(string filename);
      ~NN();
      void feedforward();

    private:
      vector<Layer<MatrixLayerTemplate<L>>*>* layers = new vector<Layer<MatrixLayerTemplate<L>>*>;
      vector<Weights<MatrixWeightsTemplate<W>>*>* weights = new vector<Weights<MatrixWeightsTemplate<W>>*>;
      unsigned int total_layers = 0;
      unsigned int total_weights = 0;
      void add_weight();
  };
};
