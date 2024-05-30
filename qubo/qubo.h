#pragma once

#include <cstdint>

namespace Qubo {
  class QuboFunc{
    public:
      QuboFunc(double P);
      double evaluate(double q1, double q2, double q3, uint8_t x1, uint8_t x2, uint8_t x3);

    private:
      double P;
  };
};
