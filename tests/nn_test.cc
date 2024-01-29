#include <stdexcept>
#include <gtest/gtest.h>
#include "../machine/machine.h"
#include "../machine/layer.h"

using Machine::NN;
using Layers::Layer;
using std::invalid_argument;

namespace {
  TEST(CreationTest, CreateEmptyNNTest){
    NN *nn = new NN;
    ASSERT_EQ(nn->get_layers()->size(), 0);
    ASSERT_EQ(nn->get_total_layers(), 0);
    delete nn;
  }

  TEST(UpdateTest, AddLayerBySizeTest){
    NN *nn = new NN;
      
    nn->add_layer(3);
    nn->add_layer(3);
    nn->add_layer(3);
    ASSERT_EQ(nn->get_total_layers(), 3);
    ASSERT_EQ(nn->get_layers()->size(), 3);
    ASSERT_EQ(nn->get_layer(0)->get_size(), 3); 
    
    delete nn;
  }

  TEST(UpdateTest, AddLayerTest){
    NN *nn = new NN;
    Layer* layer = new Layer(3);
    nn->add_layer(layer);

    ASSERT_EQ(nn->get_total_layers(), 1);
    ASSERT_EQ(nn->get_layers()->size(), 1);
    ASSERT_EQ(nn->get_layer(0)->get_size(), 3); 
    delete nn;
  }

  TEST(ValuesTest, GetLayersTest){
    NN *nn = new NN;
    nn->add_layer(3);
    nn->add_layer(3);
    nn->add_layer(3);

    ASSERT_EQ(nn->get_layers()->size(), 3);

    delete nn; 
  }

  TEST(ValuesTest, GetLayerTest){
    NN *nn = new NN;
    Layer *layer = new Layer(2);
    nn->add_layer(1);
    nn->add_layer(layer);
    nn->add_layer(3);

    ASSERT_EQ(nn->get_layer(1)->get_size(), 2);
    ASSERT_EQ(nn->get_layer(1), layer);

    delete nn; 
  }

  TEST(ValuesTest, GetLayerFromEmptyNetworkTest){
    NN *nn = new NN;
    EXPECT_THROW({ nn->get_layer(0); }, invalid_argument);
    delete nn;
  }

  TEST(ValuesTest, GetLayerOutOfBoundsTest){
    NN *nn = new NN; 
    nn->add_layer(3);
    EXPECT_NO_THROW({ nn->get_layer(0); });
    EXPECT_THROW({ nn->get_layer(1); }, invalid_argument);

    delete nn;
  }

}
