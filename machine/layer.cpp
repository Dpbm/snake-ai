#include "layer.h"
#include <stdexcept>

using Matrices::Matrix;
using std::invalid_argument;

namespace Layers {
  unsigned int size;
  Matrix *values;

  Layer::Layer(unsigned int size){
    this->size = size;
    this->values = new Matrix(size, 1);
    this->values->random(-1, 1);
  }

  Layer::Layer(Matrix *values){
    if(values->get_height() != 1)
      throw invalid_argument("Invalid values dimensions!");

    this->size = values->get_width();
    this->values = values;
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
}
