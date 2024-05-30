#include "qubo.h"
#include <cstdint>

namespace Qubo{
  QuboFunc::QuboFunc(double P){
   this->P = P;
  }
  
  double QuboFunc::evaluate(double q1, double q2, double q3, uint8_t x1, uint8_t x2, uint8_t x3){
    return  (q1*x1 + q2*x2 + q3*x3);
  }
};
