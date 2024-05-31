#pragma once

#include <cstdint>

namespace Qubo {
    static uint8_t x_combinations[8][3] = {
      {0, 0, 0},
      {0, 0, 1},
      {0, 1, 0}, 
      {0, 1, 1},
      {1, 0 ,0},
      {1, 0, 1},
      {1, 1, 0},
      {1, 1, 1}
    };

  class QuboFunc{
    public:
      QuboFunc(double P);
      double evaluate(double q0, double q1, double q2, uint8_t x0, uint8_t x1, uint8_t x2);
      uint8_t* minimize(double q0, double q1, double q2);

    private:
      double P;
  };
};
