#pragma once

#include <iostream>
#include <vector>
#include "layer.h"
#include "weights.h"
#include "../matrix/matrix.h"

using Layers::Layer;
using NNWeights::Weights;
using Matrices::MatrixTemplate;
using std::vector;
using std::string;

namespace Machine {
  template <typename T>
  class NN{  
    public:
      void add_layer(unsigned int size);
      void add_layer(Layer<MatrixTemplate<T>>* layer);
      vector<Layer<MatrixTemplate<T>>*>* get_layers();
      vector<Weights<MatrixTemplate<T>>*>* get_weights();
      Layer<MatrixTemplate<T>>* get_layer(unsigned int i);
      Weights<MatrixTemplate<T>>* get_weight(unsigned int i);
      unsigned int get_total_layers();
      unsigned int get_total_weights();
      void save_weights(string filename);
      ~NN();
      void feedforward();

    private:
      vector<Layer<MatrixTemplate<T>>*>* layers = new vector<Layer<MatrixTemplate<T>>*>;
      vector<Weights<MatrixTemplate<T>>*>* weights = new vector<Weights<MatrixTemplate<T>>*>;
      unsigned int total_layers = 0;
      unsigned int total_weights = 0;
      void add_weight();
  };
};
