#include <cmath>
#include "activation.h"
#include "../matrix/matrix.h"

using std::exp;
using std::pow;
using std::abs;
using Matrices::Matrix;

namespace Activations {
  void relu(Matrix* values){
    for(size_t i = 0; i < values->get_width(); i++){
      double x = values->get_position_value(0, i);
      values->update_value(0, i, x <= 0 ? 0 : x);
    }
  }

  void sigmoid(Matrix *values){
    for(size_t i = 0; i < values->get_width(); i++){
      double x = values->get_position_value(0, i);
      values->update_value(0, i, pow((1 + exp(-x)), -1));
    }
  }

  void tanh(Matrix *values){
    for(size_t i = 0; i < values->get_width(); i++){
      double x = values->get_position_value(0, i);
      values->update_value(0, i, abs(std::tanh(x)));
    }
  }

  void softmax(Matrix* values){
    double exps[values->get_width()];
    double total;
    for(size_t i = 0; i < values->get_width(); i++){
      double exp_value = exp(values->get_position_value(0,i)); 
      exps[i] = exp_value;
      total += exp_value;
    }

    
    for(size_t i = 0; i < values->get_width(); i++)
      values->update_value(0, i, exps[i]/total);
  }

  void f_x(Matrix* values){
    return;
  }
}
