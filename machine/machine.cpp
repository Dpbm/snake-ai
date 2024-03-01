#include <stdexcept>
#include <vector>
#include "layer.h"
#include "weights.h"
#include "machine.h"

using Layers::Layer;
using NNWeights::Weights;
using std::vector;
using std::string;
using std::invalid_argument;

namespace Machine {
  vector<Layer*>* layers;
  vector<Weights*>* weights;
  unsigned int total_layers;

   
  void NN::add_layer(unsigned int size){
    layers->push_back(new Layer(size, this->total_layers==0));
    this->total_layers++;
    this->add_weight();
  }
  
   
  void NN::add_layer(Layer* layer){
    layers->push_back(layer);
    this->total_layers++;
    this->add_weight();
  } 

   
  void NN::add_weight(){
    if(this->total_layers <= 1)
      return;
   
    unsigned int first_layer_size = layers->at(this->total_layers-2)->get_size(); 
    unsigned int second_layer_size = layers->at(this->total_layers-1)->get_size();
    this->weights->push_back(new Weights(second_layer_size, first_layer_size));
    this->total_weights++;
  }

   
  vector<Layer*>* NN::get_layers(){
    return this->layers;
  }

   
  void NN::save_weights(string filename){
    for(Weights* weight: (*this->weights))
      weight->save_weights(filename);
  }

   
  Layer* NN::get_layer(unsigned int i){
    if(this->total_layers == 0 || i > this->total_layers-1)
      throw invalid_argument("invalid layer position");

    return this->layers->at(i);
  }
  
   
  Weights* NN::get_weight(unsigned int i){
    if(this->total_weights == 0 || i > this->total_weights-1)
      throw invalid_argument("invalid weights position");
    return this->weights->at(i);
  }
  
   
  vector<Weights*>* NN::get_weights(){
    return this->weights;
  }
  

   
  unsigned int NN::get_total_layers(){
    return this->total_layers;
  }
  
   
  unsigned int NN::get_total_weights(){
    return this->total_weights;
  } 

   
  NN::~NN(){
    for(Layer *layer: (*this->layers))
      delete layer;
    for(Weights *weight: (*this->weights))
      delete weight;
  }

   
  void NN::feedforward(){
    for(unsigned int layer = 0; layer < this->total_layers-1; layer++){
      Layer* actual_layer = this->get_layer(layer);
      Layer* next_layer = this->get_layer(layer+1);

      Matrix* layer_values = actual_layer->get_values();
      Matrix* layer_weights = this->get_weight(layer)->get_weights();

      Matrix* dot_product_result = (*layer_values) * (*layer_weights);
      next_layer->set_values(dot_product_result);
      next_layer->activate_neurons();
    }
  }
}
