#pragma once

#include <cstdint>
#include <iostream>
#include "../matrix/matrix.h"

using std::string;
using Matrices::Matrix;

namespace Machine{
  
  class Weights{
    public:
      Weights(unsigned int first_layer_size, unsigned int second_layer_size);
      void load_weights(Matrix* weights);
      Matrix* get_weights();
      ~Weights();

      uint16_t get_width();
      uint16_t get_height();
      uint64_t get_total_weights();  

      void save_weights(string filename);

    private:
      unsigned int width, height;
      Matrix *weights;

  };
};
