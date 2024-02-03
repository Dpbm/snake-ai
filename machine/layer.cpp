#include "layer.h"
#include <stdexcept>

using Matrices::Matrix;
using std::invalid_argument;
using std::invalid_argument;

namespace Layers {
  bool input;
  unsigned int size;
  Matrix *values;
  double (*activation)(double);

  Layer::Layer(unsigned int size, bool input){
    this->size = size;
    this->values = new Matrix(size, 1);
    this->values->random(-1, 1);
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

  void Layer::set_activation_function(double (*activation)(double)){
    if(this->input)
      invalid_argument("Input layer must not have a activation function!");

    this->activation = activation; 
  }

  void Layer::activate_neurons(){
    double *neurons = this->values->get_row(0);
    
    for(unsigned int i = 0; i < this->size; i++){
      double neuron_value = neurons[i];
      this->values->update_value(i, 0, this->activation(neuron_value));
    }

    delete neurons;
  }
}
