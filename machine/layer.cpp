#include "layer.h"
#include "../helpers/utils.h"
#include <stdexcept>

using Matrices::Matrix;
using std::invalid_argument;
using Utils::random;

namespace Layers {
  unsigned int size;
  Matrix *values;

  Layer::Layer(unsigned int size){
    this->size = size;
    this->values = new Matrix(1, size);
    for(unsigned int i = 0; i < size; i++)
      this->values->update_value(i, 0, random(-1, 1));
  }

  Layer::Layer(Matrix *values){
    if(values->get_width() != 1)
      throw invalid_argument("Invalid values dimensions!");

    this->size = values->get_height();
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
