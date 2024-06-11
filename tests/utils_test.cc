#include <gtest/gtest.h>
#include "../helpers/utils.h"

using Utils::distance;

namespace {
  TEST(ValueTest, ZeroDistanceTest){
    ASSERT_EQ(distance(1, 1, 1, 1), 0);
  }
  
  TEST(ValueTest, AllZerosDistanceTest){
    ASSERT_EQ(distance(0, 0, 0, 0), 0);
  }
  
  TEST(ValueTest, ZeroDistanceNegativeDistanceTest){
    ASSERT_EQ(distance(-1, -2, -1, -2), 0);
  }
  
  TEST(ValueTest, GetDistanceTest){
    ASSERT_EQ(distance(1, 4, 5, 1), 5);
  }
}
