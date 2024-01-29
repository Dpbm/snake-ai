#include "machine.h"
#include "layer.h"
#include <vector>

using Layers::Layer;
using std::vector;

namespace Machine {
  vector<Layer*>* layers;
  
  void NN::add_layer(unsigned int size){
    layers->push_back(new Layer(size));
  }

  void NN::add_layer(Layer* layer){
    layers->push_back(layer);
  }  
}
