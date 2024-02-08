#include <stdexcept>
#include <vector>
#include "layer.h"
#include "weights.h"
#include "machine.h"

using Layers::Layer;
using Layers::MatrixLayerTemplate;
using NNWeights::Weights;
using NNWeights::MatrixWeightsTemplate;
using std::vector;
using std::string;
using std::invalid_argument;

namespace Machine {
  template <typename L> vector<Layer<MatrixLayerTemplate<L>>*>* layers;
  template <typename W> vector<Weights<MatrixWeightsTemplate<W>>*>* weights;
  unsigned int total_layers;

  template <typename L, typename W> 
  void NN<MatrixLayerTemplate<L>, MatrixWeightsTemplate<W>>::add_layer(unsigned int size){
    layers->push_back(new Layer<MatrixLayerTemplate<L>>(size, this->total_layers==0));
    this->total_layers++;
    this->add_weight();
  }
  
  template <typename L, typename W> 
  void NN<MatrixLayerTemplate<L>, MatrixWeightsTemplate<W>>::add_layer(Layer<MatrixLayerTemplate<L>>* layer){
    layers->push_back(layer);
    this->total_layers++;
    this->add_weight();
  } 

  template <typename L, typename W> 
  void NN<MatrixLayerTemplate<L>, MatrixWeightsTemplate<W>>::add_weight(){
    if(this->total_layers <= 1)
      return;
   
    unsigned int first_layer_size = layers->at(this->total_layers-2)->get_size(); 
    unsigned int second_layer_size = layers->at(this->total_layers-1)->get_size();
    this->weights->push_back(new Weights<MatrixWeightsTemplate<W>>(first_layer_size, second_layer_size));
    this->total_weights++;
  }

  template <typename L, typename W> 
  vector<Layer<MatrixLayerTemplate<L>>*>* NN<MatrixLayerTemplate<L>, MatrixWeightsTemplate<W>>::get_layers(){
    return this->layers;
  }

  template <typename L, typename W> 
  void NN<MatrixLayerTemplate<L>, MatrixWeightsTemplate<W>>::save_weights(string filename){
    for(Weights<MatrixWeightsTemplate<W>>* weight: (*this->weights))
      weight->save_weights(filename);
  }

  template <typename L, typename W> 
  Layer<MatrixLayerTemplate<L>>* NN<MatrixLayerTemplate<L>, MatrixWeightsTemplate<W>>::get_layer(unsigned int i){
    if(this->total_layers == 0 || i > this->total_layers-1)
      throw invalid_argument("invalid layer position");

    return this->layers->at(i);
  }
  
  template <typename L, typename W> 
  Weights<MatrixWeightsTemplate<W>>* NN<MatrixLayerTemplate<L>, MatrixWeightsTemplate<W>>::get_weight(unsigned int i){
    if(this->total_weights == 0 || i > this->total_weights-1)
      throw invalid_argument("invalid weights position");
    return this->weights->at(i);
  }
  
  template <typename L, typename W> 
  vector<Weights<MatrixWeightsTemplate<W>>*>* NN<MatrixLayerTemplate<L>, MatrixWeightsTemplate<W>>::get_weights(){
    return this->weights;
  }
  

  template <typename L, typename W> 
  unsigned int NN<MatrixLayerTemplate<L>, MatrixWeightsTemplate<W>>::get_total_layers(){
    return this->total_layers;
  }
  
  template <typename L, typename W> 
  unsigned int NN<MatrixLayerTemplate<L>, MatrixWeightsTemplate<W>>::get_total_weights(){
    return this->total_weights;
  } 

  template <typename L, typename W> 
  NN<MatrixLayerTemplate<L>, MatrixWeightsTemplate<W>>::~NN(){
    for(Layer<MatrixLayerTemplate<L>> *layer: (*this->layers))
      delete layer;
    for(Weights<MatrixWeightsTemplate<W>> *weight: (*this->weights))
      delete weight;
  }

  template <typename L, typename W> 
  void NN<MatrixLayerTemplate<L>, MatrixWeightsTemplate<W>>::feedforward(){
    for(unsigned int layer = 0; layer < this->total_layers-1; layer++){
      Layer<MatrixLayerTemplate<L>>* actual_layer = this->get_layer(layer);
      Layer<MatrixLayerTemplate<L>>* next_layer = this->get_layer(layer+1);

      Matrix<MatrixLayerTemplate<L>>* layer_values = actual_layer->get_values();
      Matrix<MatrixWeightsTemplate<W>>* layer_weights = this->get_weight(layer)->get_weights();


      //TODO: remove the & and .transpose() when (dot product returns Matrix*)
      Matrix<MatrixLayerTemplate<L>> dot_product_result = (*layer_values) * (*layer_weights);
      dot_product_result.transpose();
      next_layer->set_values(&dot_product_result);
      
      next_layer->activate_neurons();
    }
  }
}
