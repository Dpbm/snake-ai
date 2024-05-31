#include <cstdint>
#include <cmath>
#include "qubo.h"

using std::pow;

namespace Qubo{
  QuboFunc::QuboFunc(double P){
   this->P = P;
  }
  
  double QuboFunc::evaluate(double q0, double q1, double q2, uint8_t x0, uint8_t x1, uint8_t x2){
    return (q0*x0 + q1*x1 + q2*x2) + P*(pow(x0 + x1 + x2 - 1, 2));
  }

  uint8_t* QuboFunc::minimize(double q0, double q1, double q2){
    //REMEMBER TO CLEAN AFTER USING IT!
    uint8_t* result = new uint8_t[3];
    double best = 1000000000000;
   
    for(size_t i = 0; i < 8; i++){
      uint8_t x0 = x_combinations[i][0]; 
      uint8_t x1 = x_combinations[i][1]; 
      uint8_t x2 = x_combinations[i][2];

      double val = this->evaluate(q0, q1, q2, x0, x1, x2);
      
      if(val <= best){
        best = val;
        result[0] = x0; 
        result[1] = x1;
        result[2] = x2;
      }
    }

    return result; 
  }
};
