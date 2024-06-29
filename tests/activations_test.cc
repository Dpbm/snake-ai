#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../machine/activation.h"
#include "../matrix/matrix.h"

using ::testing::Gt;
using ::testing::Lt;
using Machine::relu;
using Machine::tanh;
using Machine::sigmoid;
using Machine::softmax;
using Matrices::Matrix;

namespace {
  TEST(ValuesTest, ReluTest){
    Matrix* values = new Matrix(3, 1);
    values->update_value(0, 0, -1);
    values->update_value(0, 1, 0);
    values->update_value(0, 2, 1);
    relu(values);
    ASSERT_EQ(values->get_position_value(0, 0), 0);
    ASSERT_EQ(values->get_position_value(0, 1), 0);
    ASSERT_EQ(values->get_position_value(0, 2), 1);
  }
  
  TEST(ValuesTest, SigmoidTest){
    Matrix* values = new Matrix(5, 1);
    values->update_value(0, 0, -100);
    values->update_value(0, 1, -1);
    values->update_value(0, 2, 0);
    values->update_value(0, 3, 1);
    values->update_value(0, 4, 100);
    sigmoid(values);

    ASSERT_THAT(values->get_position_value(0, 0), Lt(0.1));
    ASSERT_THAT(values->get_position_value(0, 1), Gt(0.1));
    ASSERT_EQ(values->get_position_value(0, 2), 0.5);
    ASSERT_THAT(values->get_position_value(0, 3), Gt(0.5));
    ASSERT_EQ(values->get_position_value(0, 4), 1);
  }
  
  TEST(ValuesTest, TanhTest){
    Matrix* values = new Matrix(5, 1);
    values->update_value(0, 0, -100);
    values->update_value(0, 1, -1);
    values->update_value(0, 2, 0);
    values->update_value(0, 3, 1);
    values->update_value(0, 4, 100);
    tanh(values);
    ASSERT_EQ(values->get_position_value(0, 0), 1);
    ASSERT_THAT(values->get_position_value(0, 1), Gt(0.5));
    ASSERT_EQ(values->get_position_value(0, 2), 0);
    ASSERT_THAT(values->get_position_value(0, 3), Gt(0.5));
    ASSERT_EQ(values->get_position_value(0, 4), 1);
  }

  TEST(ValuesTest, SoftmaxTest){
    Matrix* values = new Matrix(5, 1);
    values->update_value(0, 0, -100);
    values->update_value(0, 1, -1);
    values->update_value(0, 2, 0);
    values->update_value(0, 3, 1);
    values->update_value(0, 4, 100);
    softmax(values);
    ASSERT_THAT(values->get_position_value(0, 0), Lt(0.1));
    ASSERT_THAT(values->get_position_value(0, 1), Lt(0.1));
    ASSERT_THAT(values->get_position_value(0, 2), Lt(0.1));
    ASSERT_THAT(values->get_position_value(0, 3), Lt(0.1));
    ASSERT_EQ(values->get_position_value(0, 4), 1);
  }
  
}
