#include "machine.h"
#include "layer.h"
#include <stdexcept>
#include <vector>

using Layers::Layer;
using std::vector;
using std::invalid_argument;

namespace Machine {
  vector<Layer*>* layers;
  unsigned int total_layers;

  void NN::add_layer(unsigned int size){
    layers->push_back(new Layer(size));
    this->total_layers++;
  }

  void NN::add_layer(Layer* layer){
    layers->push_back(layer);
    this->total_layers++;
  }  

  vector<Layer*>* NN::get_layers(){
    return this->layers;
  }

  Layer* NN::get_layer(unsigned int i){
    if(this->total_layers == 0 || i > this->total_layers-1)
      throw invalid_argument("invalid layer position");

    return this->layers->at(i);
  }

  unsigned int NN::get_total_layers(){
    return this->total_layers;
  }

  NN::~NN(){
    for(Layer *layer: (*this->layers))
      delete layer;
  }
}
