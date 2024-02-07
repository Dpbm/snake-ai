#include <stdexcept>
#include <vector>
#include "layer.h"
#include "weights.h"
#include "machine.h"
#include "../matrix/matrix.h"

using Layers::Layer;
using NNWeights::Weights;
using Matrices::MatrixTemplate;
using std::vector;
using std::string;
using std::invalid_argument;

namespace Machine {
  template <typename T> vector<Layer<MatrixTemplate<T>>*>* layers;
  template <typename T> vector<Weights<MatrixTemplate<T>>*>* weights;
  unsigned int total_layers;

  template <typename T> void NN<T>::add_layer(unsigned int size){
    layers->push_back(new Layer<MatrixTemplate<T>>(size, this->total_layers==0));
    this->total_layers++;
    this->add_weight();
  }

  template <typename T> void NN<T>::add_layer(Layer<MatrixTemplate<T>>* layer){
    layers->push_back(layer);
    this->total_layers++;
    this->add_weight();
  } 

  template <typename T> void NN<T>::add_weight(){
    if(this->total_layers <= 1)
      return;
   
    unsigned int first_layer_size = layers->at(this->total_layers-2)->get_size(); 
    unsigned int second_layer_size = layers->at(this->total_layers-1)->get_size();
    this->weights->push_back(new Weights<MatrixTemplate<T>>(first_layer_size, second_layer_size));
    this->total_weights++;
  }

  template <typename T> vector<Layer<MatrixTemplate<T>>*>* NN<T>::get_layers(){
    return this->layers;
  }

  template <typename T> void NN<T>::save_weights(string filename){
    for(Weights<MatrixTemplate<T>>* weight: (*this->weights))
      weight->save_weights(filename);
  }

  template <typename T> Layer<MatrixTemplate<T>>* NN<T>::get_layer(unsigned int i){
    if(this->total_layers == 0 || i > this->total_layers-1)
      throw invalid_argument("invalid layer position");

    return this->layers->at(i);
  }
  
  template <typename T> Weights<MatrixTemplate<T>>* NN<T>::get_weight(unsigned int i){
    if(this->total_weights == 0 || i > this->total_weights-1)
      throw invalid_argument("invalid weights position");
    return this->weights->at(i);
  }
  
  template <typename T> vector<Weights<MatrixTemplate<T>>*>* NN<T>::get_weights(){
    return this->weights;
  }
  

  template <typename T> unsigned int NN<T>::get_total_layers(){
    return this->total_layers;
  }
  
  template <typename T> unsigned int NN<T>::get_total_weights(){
    return this->total_weights;
  } 

  template <typename T> NN<T>::~NN(){
    for(Layer<MatrixTemplate<T>> *layer: (*this->layers))
      delete layer;
    for(Weights<MatrixTemplate<T>> *weight: (*this->weights))
      delete weight;
  }

  template <typename T> void NN<T>::feedforward(){
    for(unsigned int layer = 0; layer < this->total_layers-1; layer++){
      Layer<MatrixTemplate<T>>* actual_layer = this->get_layer(layer);
      Layer<MatrixTemplate<T>>* next_layer = this->get_layer(layer+1);

      Matrix<MatrixTemplate<T>>* layer_values = actual_layer->get_values();
      Matrix<MatrixTemplate<T>>* layer_weights = this->get_weight(layer)->get_weights();


      //TODO: remove the & and .transpose() when (dot product returns Matrix*)
      Matrix<MatrixTemplate<T>> dot_product_result = (*layer_values) * (*layer_weights);
      dot_product_result.transpose();
      next_layer->set_values(&dot_product_result);
      
      next_layer->activate_neurons();
    }
  }
}
