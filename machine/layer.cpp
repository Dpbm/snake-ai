#include <stdexcept>
#include "layer.h"

using Matrices::Matrix;
using std::invalid_argument;

namespace Machine{
  Layer::Layer(unsigned int size, bool input){
    this->size = size;
    this->values = new Matrix(size, 1);
    this->input = input;
  }

  Layer::Layer(Matrix *values, bool input){
    if(values->get_height() != 1)
      throw invalid_argument("Invalid values dimensions!");

    this->size = values->get_width();
    this->values = values;
    this->input = input;
  }

  Matrix* Layer::get_values(){
    return this->values;
  }

  Layer::~Layer(){
    delete this->values;
  }

  unsigned int Layer::get_size() const {
    return this->size;
  }

  void Layer::activate_neurons(){
    this->activation(this->values); 
  }

  bool Layer::is_input(){
    return this->input;
  }

  void Layer::set_values(Matrix* values){
    if(values->get_width() != this->size || values->get_height() != 1)
      throw invalid_argument("The new values matrix must have the size dimensions as defined!");
    
    delete this->values;
    this->values = values;
  }

  void Layer::set_activation_function(void(*activation)(Matrix*)){
   if(this->input)
      throw invalid_argument("Input layer must not have a activation function!");   
    this->activation = activation;
  }

  void (*Layer::get_activation_function())(Matrix*){
    return this->activation;
  }
}
