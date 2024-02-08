#include "layer.h"
#include <stdexcept>

using Matrices::Matrix;
using std::invalid_argument;
using std::invalid_argument;

namespace Layers {
  bool input;
  unsigned int size;
  template <typename T> Matrix<MatrixLayerTemplate<T>> *values;
  double (*activation)(double);

  template <typename T> Layer<MatrixOfNumbersTemplate<T>>::Layer(unsigned int size, bool input){
    this->size = size;
    this->values = new Matrix<MatrixOfNumbersTemplate<T>>(size, 1);
    this->values->random(-1, 1);
    this->input = input;
  }

  template <typename T> Layer<MatrixLayerTemplate<T>>::Layer(Matrix<MatrixLayerTemplate<T>> *values, bool input){
    if(values->get_height() != 1)
      throw invalid_argument("Invalid values dimensions!");

    this->size = values->get_width();
    this->values = values;
    this->input = input;
  }

  template <typename T> Matrix<MatrixLayerTemplate<T>>* Layer<MatrixLayerTemplate<T>>::get_values(){
    return this->values;
  }

  template <typename T> Layer<MatrixLayerTemplate<T>>::~Layer(){
    delete this->values;
  }

  template <typename T> unsigned int Layer<MatrixLayerTemplate<T>>::get_size() const {
    return this->size;
  }

  template <typename T> void Layer<MatrixLayerTemplate<T>>::set_activation_function(double (*activation)(double)){
    if(this->input)
      throw invalid_argument("Input layer must not have a activation function!");

    this->activation = activation; 
  }

  template <typename T> void Layer<MatrixLayerTemplate<T>>::activate_neurons(){
    for(unsigned int i = 0; i < this->size; i++){
      double neuron_value = this->values->get_position_value(0, i);
      this->values->update_value(0, i, this->activation(neuron_value));
    }
  }

  template <typename T> bool Layer<MatrixLayerTemplate<T>>::is_input(){
    return this->input;
  }

  template <typename T> double (*Layer<MatrixLayerTemplate<T>>::get_activation_function())(double){
    return this->activation;
  }

  template <typename T> void Layer<MatrixLayerTemplate<T>>::set_values(Matrix<MatrixLayerTemplate<T>>* values){
    if(values->get_width() != this->size || values->get_height() != 1)
      throw invalid_argument("The new values matrix must have the size dimensions as defined!");
    
    delete this->values;
    this->values = values;
  }
}
