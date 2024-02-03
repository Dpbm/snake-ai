#include <stdexcept>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "../matrix/matrix.h"
#include "../machine/layer.h"
#include "../machine/activation.h"

using Matrices::Matrix;
using Layers::Layer;
using std::invalid_argument;
using ::testing::AllOf;
using ::testing::Ge;
using ::testing::Le;
using Activations::relu;

namespace {

  TEST(CreationTest, CreateLayerBySizeTest){
    Layer* layer = new Layer(3, true);
    ASSERT_EQ(layer->get_size(), 3);
    ASSERT_EQ(layer->get_values()->get_height(), 1);
    ASSERT_EQ(layer->get_values()->get_width(), 3);
    delete layer;
  }

  TEST(CreationTest, CreateLayerByMatrixTest){
    Matrix* values = new Matrix(3, 1);
    Layer* layer = new Layer(values, true);
    
    ASSERT_EQ(layer->get_size(), 3);
    ASSERT_EQ(layer->get_values(), values);
    ASSERT_EQ(layer->get_values()->get_width(), 3);
    ASSERT_EQ(layer->get_values()->get_height(), 1);

    delete layer;
  }

  TEST(CreationTest, CreateLayerWithInvalidWidhtTest){
    Matrix* values = new Matrix(3, 3);
    EXPECT_THROW({ new Layer(values, true); }, invalid_argument);
    delete values;
  }

  TEST(ValuesTest, GetValuesTest){
    Layer *layer = new Layer(1, true);
    ASSERT_THAT(layer->get_values()->get_position_value(0, 0), AllOf(Ge(-1), Le(1)));
    delete layer;
  }

  TEST(UpdateTest, SetActivationFunctionTest){
    Layer *layer = new Layer(1, false);
    layer->set_activation_function(&relu);
    double (*activation)(double) = layer->get_activation_function();
    ASSERT_EQ(activation, &relu);
    delete layer;
  }
  
  TEST(UpdateTest, InvaliActivationFunctionForInputLayerTest){
    Layer *layer = new Layer(1, true);
    EXPECT_THROW({ layer->set_activation_function(&relu); }, invalid_argument);
    delete layer;
  }

  TEST(UpdateTest, ActivateNeuronsTest){
    Matrix* values = new Matrix(2, 1);
    values->update_value(0, 0, -15);
    values->update_value(0, 1, 12);
  
    Layer *layer = new Layer(values, false);
    layer->set_activation_function(&relu);
    
    layer->activate_neurons();
    ASSERT_EQ(layer->get_values()->get_position_value(0, 0), 0);
    ASSERT_EQ(layer->get_values()->get_position_value(0, 1), 12);
    delete layer;
  }
  
  TEST(ValuesTest, InputLayerTest){
    Layer* layer = new Layer(1, true);
    ASSERT_EQ(layer->is_input(), true);
    delete layer;
  }
  
  TEST(ValuesTest, NonInputLayerTest){
    Layer* layer = new Layer(1, false);
    ASSERT_EQ(layer->is_input(), false);
    delete layer;
  }
}
