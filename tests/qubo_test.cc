#include <cstdint>
#include <gtest/gtest.h>
#include "../qubo/qubo.h"

using Qubo::QuboFunc;

namespace {
  TEST(ValueTest, EvaluateAllZerosTest){
    QuboFunc q(1);
    ASSERT_EQ(q.evaluate(1, 1, 1, 0, 0, 0), 1);
  }
  
  TEST(ValueTest, EvaluateDifferentBiStringTest){
    QuboFunc q(1);
    ASSERT_EQ(q.evaluate(2, 1, 2, 0, 1, 0), 1);
  }
  
  TEST(ValueTest, EvaluateAllOnesTest){
    QuboFunc q(1);
    ASSERT_EQ(q.evaluate(2, 1, 2, 1, 1, 1), 9);
  }

  TEST(ValueTest, MinimizeTest){
    QuboFunc q(1);
    
    uint8_t* result = q.minimize(1, 1, 1);

    ASSERT_EQ(result[0], 1);
    ASSERT_EQ(result[1], 0);
    ASSERT_EQ(result[2], 0);
  }  
}
