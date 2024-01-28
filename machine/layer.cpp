#include "layer.h"
#include <stdexcept>

using Matrices::Matrix;

namespace Layers {
  unsigned int size;
  Matrix *values;

  InputLayer::InputLayer(unsigned int size){
    this->size = size;
  }

  void InputLayer::set_node_values(Matrix *values){
    if(values->get_width() != 1 || values->get_height() != this->size)
      throw std::invalid_argument("Invalid values dimensions!");

    this->values = values;
  }

  InputLayer::~InputLayer(){
    delete this->values;
  }
}
