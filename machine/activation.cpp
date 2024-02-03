#include <cmath>
#include "activation.h"

using std::exp;
using std::pow;

namespace Activations {
  double relu(double x){
    return x <= 0 ? 0 : x;
  }

  double sigmoid(double x){
    return pow((1 + exp(-x)), -1);
  }
}
