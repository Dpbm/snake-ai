#include <stdexcept>
#include "layer.h"

using Matrices::Matrix;
using std::invalid_argument;

namespace Layers {
  bool input;
  unsigned int size;
  Matrix<double> *values;
  double (*activation)(double);

  Layer::Layer(unsigned int size, bool input){
    this->size = size;
    this->values = new Matrix<double>(size, 1);
    this->input = input;
  }

  Layer::Layer(Matrix<double> *values, bool input){
    if(values->get_height() != 1)
      throw invalid_argument("Invalid values dimensions!");

    this->size = values->get_width();
    this->values = values;
    this->input = input;
  }

  Matrix<double>* Layer::get_values(){
    return this->values;
  }

  Layer::~Layer(){
    delete this->values;
  }

  unsigned int Layer::get_size() const {
    return this->size;
  }

  void Layer::set_activation_function(double (*activation)(double)){
    if(this->input)
      throw invalid_argument("Input layer must not have a activation function!");

    this->activation = activation; 
  }

  void Layer::activate_neurons(){
    for(unsigned int i = 0; i < this->size; i++){
      double neuron_value = this->values->get_position_value(0, i);
      this->values->update_value(0, i, this->activation(neuron_value));
    }
  }

  bool Layer::is_input(){
    return this->input;
  }

  double (*Layer::get_activation_function())(double){
    return this->activation;
  }

  void Layer::set_values(Matrix<double>* values){
    if(values->get_width() != this->size || values->get_height() != 1)
      throw invalid_argument("The new values matrix must have the size dimensions as defined!");
    
    delete this->values;
    this->values = values;
  }
}
