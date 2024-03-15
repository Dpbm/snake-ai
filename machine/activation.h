#pragma  once

#include "../matrix/matrix.h"

using Matrices::Matrix;

namespace Machine {
  void relu(Matrix* values);
  void tanh(Matrix* values);
  void sigmoid(Matrix* values);
  void softmax(Matrix* values);
  void f_x(Matrix* values);
}
