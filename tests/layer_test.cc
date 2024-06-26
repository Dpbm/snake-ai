#include <stdexcept>
#include <gtest/gtest.h>
#include "../matrix/matrix.h"
#include "../machine/layer.h"
#include "../machine/activation.h"

using std::invalid_argument;
using Matrices::Matrix;
using Machine::Layer;
using Machine::relu;
using Machine::sigmoid;
using Machine::softmax;
using Machine::tanh;

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
    Layer*layer = new Layer(1, true);
    layer->get_values()->map_to_a_single_value(3); 
    ASSERT_EQ(layer->get_values()->get_position_value(0, 0), 3);
    delete layer;
  }

  TEST(UpdateTest, SetActivationFunctionReluTest){
    Layer*layer = new Layer(1, false);
    layer->relu();
    void (*activation)(Matrix*) = layer->get_activation_function();
    ASSERT_EQ(activation, &relu);
    delete layer;
  }
  
  TEST(UpdateTest, SetActivationFunctionSigmoidTest){
    Layer*layer = new Layer(1, false);
    layer->sigmoid();
    void (*activation)(Matrix*) = layer->get_activation_function();
    ASSERT_EQ(activation, &sigmoid);
    delete layer;
  }

  TEST(UpdateTest, SetActivationFunctionTanhTest){
    Layer*layer = new Layer(1, false);
    layer->tanh();
    void (*activation)(Matrix*) = layer->get_activation_function();
    ASSERT_EQ(activation, &tanh);
    delete layer;
  }

  TEST(UpdateTest, SetActivationFunctionSoftmaxTest){
    Layer*layer = new Layer(1, false);
    layer->softmax();
    void (*activation)(Matrix*) = layer->get_activation_function();
    ASSERT_EQ(activation, &softmax);
    delete layer;
  }
  
  TEST(UpdateTest, InvaliActivationFunctionForInputLayerTest){
    Layer*layer = new Layer(1, true);
    EXPECT_THROW({ layer->relu(); }, invalid_argument);
    delete layer;
  }

  TEST(UpdateTest, ActivateNeuronsTest){
    Matrix* values = new Matrix(2, 1);
    values->update_value(0, 0, -15);
    values->update_value(0, 1, 12);
  
    Layer* layer = new Layer(values, false);
    layer->relu();
    
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

  TEST(UpdateTest, SetValuesTest){
    Layer* layer = new Layer(3, true);
    Matrix* new_values = new Matrix(3,1);
    new_values->map_to_a_single_value(1);
    layer->set_values(new_values);
    ASSERT_EQ(layer->get_values()->get_position_value(0,0), 1);
    ASSERT_EQ(layer->get_values()->get_position_value(0,1), 1);
    ASSERT_EQ(layer->get_values()->get_position_value(0,2), 1);
    delete layer;
  }

  TEST(UpdateTest, SetValuesCheckPointersTest){
    Matrix* values = new Matrix(3,1);
    Layer* layer = new Layer(values, true);
    Matrix* values2 = new Matrix(3,1);
    layer->set_values(values2);  
    ASSERT_EQ(layer->get_values(), values2);
    delete layer;
  }

  TEST(UpdateTest, SetValuesDifferentWidthTest){
    Matrix* values = new Matrix(3,1);
    Layer* layer = new Layer(values, true);
    Matrix* values2 = new Matrix(7,1);
    EXPECT_THROW({ layer->set_values(values2); }, invalid_argument);
    delete layer;
    delete values2;
  } 

  TEST(UpdateTest, SetValuesDifferentHeightTest){
    Matrix* values = new Matrix(3,1);
    Layer* layer = new Layer(values, true);
    Matrix* values2 = new Matrix(3,2);
    EXPECT_THROW({ layer->set_values(values2); }, invalid_argument);
    delete layer;
    delete values2;
  } 
}
