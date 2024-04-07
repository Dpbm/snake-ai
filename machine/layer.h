#pragma once

#include <cstdint>
#include <iostream>
#include <string>
#include "../matrix/matrix.h"

using std::string;
using Matrices::Matrix;

namespace Machine{
  class Layer{
    public:
      Layer(uint16_t size, bool input);
      Layer(Matrix *values, bool input);
      Matrix* get_values();
      unsigned int get_size() const;
      ~Layer();
      void activate_neurons();
      bool is_input();
      void set_values(Matrix* values);
      void (*get_activation_function())(Matrix*);
     
      void relu();
      void sigmoid();
      void tanh();
      void softmax();
      
      string get_activation_name();

    private:
      string activation_name = "none";
      uint16_t size = 0;
      bool input = false;
      Matrix *values = nullptr;
      void(*activation)(Matrix*);
      void set_activation_function(void(*activation)(Matrix*));
  };
};
