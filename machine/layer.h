#pragma once

#include <iostream>
#include "../matrix/matrix.h"

using Matrices::Matrix;

namespace Machine{
  class Layer{
    public:
      Layer(unsigned int size, bool input);
      Layer(Matrix *values, bool input);
      Matrix* get_values();
      unsigned int get_size() const;
      ~Layer();
      void activate_neurons();
      bool is_input();
      void set_values(Matrix* values);
      void set_activation_function(void(*activation)(Matrix*));
      void (*get_activation_function())(Matrix*);
    
    private:
      unsigned int size;
      bool input = false;
      Matrix *values = nullptr;
      void(*activation)(Matrix*);
  };
};
