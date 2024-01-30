#include "../machine/layer.h"
#include <stdexcept>
#include "../matrix/matrix.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using Matrices::Matrix;
using Layers::Layer;
using std::invalid_argument;
using ::testing::AllOf;
using ::testing::Ge;
using ::testing::Le;

namespace {

  TEST(CreationTest, CreateLayerBySizeTest){
    Layer* layer = new Layer(3);
    ASSERT_EQ(layer->get_size(), 3);
    ASSERT_EQ(layer->get_values()->get_height(), 1);
    ASSERT_EQ(layer->get_values()->get_width(), 3);
    delete layer;
  }

  TEST(CreationTest, CreateLayerByMatrixTest){
    Matrix* values = new Matrix(3, 1);
    Layer* layer = new Layer(values);
    
    ASSERT_EQ(layer->get_size(), 3);
    ASSERT_EQ(layer->get_values(), values);
    ASSERT_EQ(layer->get_values()->get_width(), 3);
    ASSERT_EQ(layer->get_values()->get_height(), 1);

    delete layer;
  }

  TEST(CreationTest, CreateLayerWithInvalidWidhtTest){
    Matrix* values = new Matrix(3, 3);
    EXPECT_THROW({ new Layer(values); }, invalid_argument);
    delete values;
  }

  TEST(ValuesTest, GetValuesTest){
    Layer *layer = new Layer(1);
    ASSERT_THAT(layer->get_values()->get_position_value(0, 0), AllOf(Ge(-1), Le(1)));
    delete layer;
  }

}
