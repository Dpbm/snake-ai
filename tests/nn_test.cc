#include <stdexcept>
#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include "../machine/machine.h"
#include "../machine/layer.h"

using std::invalid_argument;
using std::ifstream;
using std::string;
using std::getline;
using Machine::NN;
using Machine::Layer;

namespace {
  TEST(CreationTest, CreateEmptyNNTest){
    NN* nn = new NN;
    ASSERT_EQ(nn->get_layers().size(), 0);
    ASSERT_EQ(nn->get_total_layers(), 0);
    delete nn;
  }

  TEST(UpdateTest, AddLayerBySizeTest){
    NN* nn = new NN;
      
    nn->add_layer(3);
    nn->add_layer(3);
    nn->add_layer(3);
    ASSERT_EQ(nn->get_total_layers(), 3);
    ASSERT_EQ(nn->get_layers().size(), 3);
    ASSERT_EQ(nn->get_layer(0)->get_size(), 3); 
    
    delete nn;
  }

  TEST(UpdateTest, AddLayerTest){
    NN* nn = new NN;
    Layer* layer = new Layer(3, true);
    nn->add_layer(layer);

    ASSERT_EQ(nn->get_total_layers(), 1);
    ASSERT_EQ(nn->get_layers().size(), 1);
    ASSERT_EQ(nn->get_layer(0)->get_size(), 3); 
    delete nn;
  }
  
  TEST(UpdateTest, AddLayerMixTest){
    NN* nn = new NN;
    Layer* layer = new Layer(3, true);
    nn->add_layer(layer);
    nn->add_layer(10);

    ASSERT_EQ(nn->get_total_layers(), 2);
    ASSERT_EQ(nn->get_layers().size(), 2);
    ASSERT_EQ(nn->get_layer(0)->get_size(), 3); 
    ASSERT_EQ(nn->get_layer(1)->get_size(), 10); 
    delete nn;
  }

  TEST(ValuesTest, GetLayersTest){
    NN* nn = new NN;
    nn->add_layer(3);
    nn->add_layer(3);
    nn->add_layer(3);

    ASSERT_EQ(nn->get_layers().size(), 3);

    delete nn; 
  }

  TEST(ValuesTest, GetLayerTest){
    NN* nn = new NN;
    Layer* layer = new Layer(2, true);
    nn->add_layer(1);
    nn->add_layer(layer);
    nn->add_layer(3);

    ASSERT_EQ(nn->get_layer(1)->get_size(), 2);
    ASSERT_EQ(nn->get_layer(1), layer);

    delete nn; 
  }

  TEST(ValuesTest, GetLayerFromEmptyNetworkTest){
    NN* nn = new NN;
    EXPECT_THROW({ nn->get_layer(0); }, invalid_argument);
    delete nn;
  }

  TEST(ValuesTest, GetLayerOutOfBoundsTest){
    NN* nn = new NN; 
    nn->add_layer(3);
    EXPECT_NO_THROW({ nn->get_layer(0); });
    EXPECT_THROW({ nn->get_layer(1); }, invalid_argument);
    delete nn;
  }

  TEST(ValuesTest, NoWeightsAddedTest){
    NN* nn = new NN;
    ASSERT_EQ(nn->get_total_weights(), 0);
    ASSERT_EQ(nn->get_weights().size(), 0);
    delete nn;
  }
  
  TEST(ValuesTest, NoWeightsAddedForASingleLayerTest){
    NN* nn = new NN;
    nn->add_layer(3);
    ASSERT_EQ(nn->get_total_weights(), 0);
    ASSERT_EQ(nn->get_weights().size(), 0);
    delete nn;
  }

  TEST(ValuesTest, AddWeightsTest){
    NN* nn = new NN;
    nn->add_layer(3);
    nn->add_layer(3);
    nn->add_layer(3);
    ASSERT_EQ(nn->get_total_weights(), 2);
    ASSERT_EQ(nn->get_weights().size(), 2);
    delete nn;
  }

  TEST(ValuesTest, SaveWeightsTest){
    NN* nn = new NN;
    nn->add_layer(1);
    nn->add_layer(3);
    nn->save_weights("test_save_from_nn.wg");
    ifstream file("test_save_from_nn.wg");
    
    string line;
    int lines;
    for(lines = 0; getline(file,line); lines++);

    ASSERT_NE(&file, nullptr);
    ASSERT_EQ(lines, 4);

    file.close();
    delete nn;
  }
  
  TEST(ValuesTest, SaveWeightsWithEntireArchTest){
    NN* nn = new NN;
    nn->add_layer(1);
    nn->add_layer(3);
    nn->add_layer(3);

    nn->get_layer(1)->relu();
    nn->get_layer(2)->relu();
    nn->save_weights("test_save_from_nn_2.wg");
    ifstream file("test_save_from_nn_2.wg");
    
    string line;
    int lines;
    for(lines = 0; getline(file,line); lines++);

    ASSERT_NE(&file, nullptr);
    ASSERT_EQ(lines, 8);

    file.close();
    delete nn;
  }
  
  TEST(ValuesTest, SaveArchOnlyTest){
    NN* nn = new NN;
    nn->save_weights("test_save_from_nn_3.wg");
    ifstream file("test_save_from_nn_3.wg");
    
    int lines;
    string line;
    for(lines = 0; getline(file,line); lines++);
    
    ASSERT_NE(&file, nullptr);
    ASSERT_EQ(lines, 1);

    file.close();
    delete nn;
  }
    
  TEST(ValuesTest, SaveArchOnlyForOneLayerTest){
    NN* nn = new NN;
    nn->add_layer(1);
    nn->save_weights("test_save_from_nn_4.wg");
    ifstream file("test_save_from_nn_4.wg");
    
    int lines;
    string line;
    for(lines = 0; getline(file,line); lines++);
    
    ASSERT_NE(&file, nullptr);
    ASSERT_EQ(lines, 1);
    file.close();
    delete nn;
  }
  
  TEST(ValuesTest, SaveWeightsWithEntireArchNoActivationTest){
    NN* nn = new NN;
    nn->add_layer(1);
    nn->add_layer(3);
    nn->add_layer(3);

    nn->save_weights("test_save_from_nn_5.wg");
    ifstream file("test_save_from_nn_5.wg");
    
    string line;
    int lines;
    for(lines = 0; getline(file,line); lines++);

    ASSERT_NE(&file, nullptr);
    ASSERT_EQ(lines, 8);

    file.close();
    delete nn;
  }
   
  TEST(ValuesTest, GetWeightTest){
    NN* nn = new NN;
    nn->add_layer(1);
    nn->add_layer(2);
    ASSERT_EQ(nn->get_weight(0)->get_width(), 2);
    ASSERT_EQ(nn->get_weight(0)->get_height(), 1);
    delete nn;
  }

  TEST(ValuesTest, GetWeightOutOfBoundsTest){
    NN* nn = new NN;
    nn->add_layer(1);
    nn->add_layer(2);
    EXPECT_THROW({ nn->get_weight(1); }, invalid_argument);
    delete nn;
  }


  TEST(ValuesTest, GetWeightWithoutWeightsBeingDefinedTest){
    NN* nn = new NN;
    EXPECT_THROW({ nn->get_weight(0); }, invalid_argument);
    delete nn;
  }
  
  TEST(CreationTest, CheckInputAndHiddenLayersTest){
    NN* nn = new NN;
    nn->add_layer(1);
    nn->add_layer(2);
    ASSERT_EQ(nn->get_layer(0)->is_input(), true);
    ASSERT_EQ(nn->get_layer(1)->is_input(), false);
    delete nn;
  }
}
