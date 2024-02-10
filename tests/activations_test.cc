#include <gtest/gtest.h>
#include "../machine/activation.h"

using Activations::relu;
using Activations::sigmoid;

namespace {
  TEST(ValuesTest, ReluZeroTest){
    ASSERT_EQ(relu(0), 0);
  }

  TEST(ValuesTest, ReluNegativeTest){
    ASSERT_EQ(relu(-1), 0);
  }
  
  TEST(ValuesTest, ReluPositiveTest){
    ASSERT_EQ(relu(2), 2);
  }
  
  TEST(ValuesTest, SigmoidZeroTest){
    ASSERT_EQ(sigmoid(0), 0.5);
  }
  
  TEST(ValuesTest, SigmoidPositiveTest){
    EXPECT_NEAR(sigmoid(20), 1, 0.2);
  }
  
  TEST(ValuesTest, SigmoidNegativeTest){
    EXPECT_NEAR(sigmoid(-20), 0, 0.2);
  }
}
