#include "layer.h"
#include <stdexcept>

using Matrices::Matrix;

namespace Layers {
  unsigned int width, height;
  Matrix *values;

  InputLayer::InputLayer(unsigned int width, unsigned int height){
    this->width = width;
    this->height = height;
  }

  void InputLayer::set_node_values(Matrix *values){
    if(values->get_width() != this->width || values->get_height() != this->height)
      throw std::invalid_argument("Invalid values dimensions!");

    this->values = values;
  }

  InputLayer::~InputLayer(){
    delete this->values;
  }
}
