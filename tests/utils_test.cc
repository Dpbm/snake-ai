#include <cstdint>
#include <fstream>
#include <gtest/gtest.h>
#include <stdexcept>
#include "../helpers/utils.h"
#include "../matrix/matrix.h"
#include "../machine/machine.h"
#include "../machine/layer.h"
#include "../machine/weights.h"

using std::getline;
using std::ifstream;
using std::invalid_argument;
using Matrices::Matrix;
using Utils::distance;
using Utils::parse_nn_arch;
using Utils::parse_nn;
using Utils::parse_weights_head;
using Utils::parse_layers_sizes;
using Utils::parse_activations;
using Utils::parse_row;
using Utils::create_file;
using Utils::append_to_file;
using Machine::NN;
using Machine::Layer;
using Machine::Weights;

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

  TEST(ValueTest, ParseNNArchNoValuesTest){
    string arch = "";
    EXPECT_THROW({parse_nn_arch(arch);}, invalid_argument);
  }  
  
  TEST(ValueTest, ParseNNArchAllValuesTest){
    string arch = "1,10,100.";
    uint8_t* result = parse_nn_arch(arch);

    ASSERT_EQ(result[0], 1);
    ASSERT_EQ(result[1], 10);
    ASSERT_EQ(result[2], 100);

    delete result;
  }  
  
  TEST(ValueTest, ParseNNArchAllValuesIgnoreRestTest){
    string arch = "1,10,100.30,20,10.";
    uint8_t* result = parse_nn_arch(arch);

    ASSERT_EQ(result[0], 1);
    ASSERT_EQ(result[1], 10);
    ASSERT_EQ(result[2], 100);

    delete result;
  }  
  
  TEST(ValueTest, ParseNNArchAllValuesDifferentParsingSymbolsTest){
    string arch = "1.10.100,";
    EXPECT_THROW({parse_nn_arch(arch);}, invalid_argument);
  }  
  
  TEST(ValueTest, ParseNNArchAllValuesMissingEndingSymbolTest){
    string arch = "1,10,100";
    EXPECT_THROW({parse_nn_arch(arch);}, invalid_argument);
  }
  
  TEST(ValueTest, ParseNNArchMoreThan3ValuesTest){
    string arch = "1,10,100,1000,10000.";
    EXPECT_THROW({ parse_nn_arch(arch); }, invalid_argument);
  }

  TEST(ValueTest, ParseEmptyWeightsHeadTest){
    string head = "";
    EXPECT_THROW({ parse_weights_head(head); }, invalid_argument);
  }
  
  TEST(ValueTest, ParseWeightsHeadMoreThan2ValuesTest){
    string head = "l10,20,30,40,50.";
    EXPECT_THROW({ parse_weights_head(head); }, invalid_argument);
  }
  
  TEST(ValueTest, ParseWeightsHeadMoreNoStopSignTest){
    string head = "l10,20";
    EXPECT_THROW({ parse_weights_head(head); }, invalid_argument);
  }
  
  TEST(ValueTest, ParseWeightsHeadLessThan2ValuesTest){
    string head = "l10.";
    EXPECT_THROW({ parse_weights_head(head); }, invalid_argument);
  }
  
  TEST(ValueTest, ParseWeightsHeadAllCorrectValuesTest){
    string head = "l10,10.";
    Matrix* result = parse_weights_head(head);

    ASSERT_EQ(result->get_width(), 10);
    ASSERT_EQ(result->get_height(), 10);
    delete result;
  }
  
  TEST(ValueTest, ParseWeightsHeadAllCorrectValuesIgnoreRestTest){
    string head = "l10,10.20,30.";
    Matrix* result = parse_weights_head(head);

    ASSERT_EQ(result->get_width(), 10);
    ASSERT_EQ(result->get_height(), 10);
    delete result;
  }
  
  TEST(ValueTest, ParseLayersSizesEmptyLineTest){
    string line = "";
    EXPECT_THROW({ parse_layers_sizes(line, 1); }, invalid_argument);
  }
  
  TEST(ValueTest, ParseLayersSizesTotalSizesAndInputLayersDoesntMatchLessThanArgumentTest){
    string line = "10,10.";
    EXPECT_THROW({ parse_layers_sizes(line, 3); }, invalid_argument);
  }
  
  TEST(ValueTest, ParseLayersSizesTotalSizesAndInputLayersDoesntMatchMoreThanArgumentTest){
    string line = "10,10,10,10.";
    EXPECT_THROW({ parse_layers_sizes(line, 3); }, invalid_argument);
  }
  
  TEST(ValueTest, ParseLayersSizesUnexpectedSepartionTest){
    string line = "10.10,10.";
    EXPECT_THROW({ parse_layers_sizes(line, 3); }, invalid_argument);
  }
  
  TEST(ValueTest, ParseLayersSizesAllCorrectValuesTest){
    string line = "10,30.";
    uint8_t* result = parse_layers_sizes(line, 2);

    ASSERT_EQ(result[0], 10);
    ASSERT_EQ(result[1], 30);
    delete result;
  }
  
  TEST(ValueTest, ParseLayersSizesAllCorrectValuesIgnoreRestTest){
    string line = "10,30.40,30.";
    uint8_t* result = parse_layers_sizes(line, 2);

    ASSERT_EQ(result[0], 10);
    ASSERT_EQ(result[1], 30);
    delete result;
  }

  TEST(ValueTest, ParseActivationsEmptyLineTest){
    string line = "";
    EXPECT_THROW({ parse_activations(line, 3); }, invalid_argument);
  }
  
  TEST(ValueTest, ParseActivationsLessThanTotalActivationsTest){
    string line = "relu,sigmoid.";
    EXPECT_THROW({ parse_activations(line, 3); }, invalid_argument);
  }
  
  TEST(ValueTest, ParseActivationsMoreThanTotalActivationsTest){
    string line = "relu,sigmoid,relu,relu.";
    EXPECT_THROW({ parse_activations(line, 3); }, invalid_argument);
  }
  
  TEST(ValueTest, ParseActivationsWrongSignSequenceTest){
    string line = "relu.sigmoid,relu.";
    EXPECT_THROW({ parse_activations(line, 3); }, invalid_argument);
  }


  TEST(ValueTest, ParseActivationsCorrectValuesTest){
    string line = "relu,sigmoid,tanh,softmax,none,test.";
    uint8_t* result = parse_activations(line, 6);

    ASSERT_EQ(result[0], 0);
    ASSERT_EQ(result[1], 1);
    ASSERT_EQ(result[2], 2);
    ASSERT_EQ(result[3], 3);
    ASSERT_EQ(result[4], 4);
    ASSERT_EQ(result[5], 4);
    delete result;
  }
  
  TEST(ValueTest, ParseActivationsCorrectValuesIgnoreRestTest){
    string line = "relu,sigmoid,tanh,softmax,none,test.relu,softmax.";
    uint8_t* result = parse_activations(line, 6);

    ASSERT_EQ(result[0], 0);
    ASSERT_EQ(result[1], 1);
    ASSERT_EQ(result[2], 2);
    ASSERT_EQ(result[3], 3);
    ASSERT_EQ(result[4], 4);
    ASSERT_EQ(result[5], 4);
    delete result;
  }
  
  TEST(ValueTest, ParseRowEmptyLineTest){
    string line = "";
    EXPECT_THROW({ parse_row(line, 3); }, invalid_argument);
  }
  
  TEST(ValueTest, ParseRowLessThanTotalWidthTest){
    string line = "30.2,30.3;";
    EXPECT_THROW({ parse_row(line, 3); }, invalid_argument);
  }
  
  TEST(ValueTest, ParseRowMoreThanTotalWidthTest){
    string line = "30.2,30.3,30.4,30.5;";
    EXPECT_THROW({ parse_row(line, 3); }, invalid_argument);
  }
  
  TEST(ValueTest, ParseRowWrongSignSequenceTest){
    string line = "30.3;30.4,405.3;";
    EXPECT_THROW({ parse_row(line, 3); }, invalid_argument);
  }


  TEST(ValueTest, ParseRowCorrectValuesTest){
    string line = "30.4,30.5;";
    double* result = parse_row(line, 2);

    ASSERT_EQ(result[0], 30.4);
    ASSERT_EQ(result[1], 30.5);
    delete result;
  }
  
  TEST(ValueTest, ParseRowCorrectValuesIgnoreRestTest){
    string line = "30.4,30.5;30.6,304.5;";
    double* result = parse_row(line, 2);

    ASSERT_EQ(result[0], 30.4);
    ASSERT_EQ(result[1], 30.5);
    delete result;
  }

  
  TEST(ValueTest, CreateFileTest){
    string data = "anything!";
    string filename = "test.txt";
    
    create_file(filename, data);

    ifstream file(filename);
    ASSERT_TRUE(file.good());
    
    string line;
    getline(file, line);
    ASSERT_EQ(line, data);
    
    file.close();
  }
  
  TEST(ValueTest, AppendToFileTest){
    string filename = "test2.txt";
    string data1 = "test1";
    string data2 = "test2";
    
    append_to_file(filename, data1);
    append_to_file(filename, "\n");
    append_to_file(filename, data2);

    ifstream file(filename);
    ASSERT_TRUE(file.good());
    
    string line1;
    string line2;
    getline(file, line1);
    file.seekg(data1.size()+1);
    getline(file, line2);
    ASSERT_EQ(line1, data1);
    ASSERT_EQ(line2, data2);
    
    file.close();
  }

  TEST(ValueTest, ParseNNTest){
    string filename = "test3.wg";
    
    append_to_file(filename, "1,1,1.\n");
    append_to_file(filename, "2,2,2.\n");
    append_to_file(filename, "relu,softmax.\n");
    append_to_file(filename, "l2,2.\n");
    append_to_file(filename, "0.3,0.4;\n");
    append_to_file(filename, "0.5,0.6;\n");
    append_to_file(filename, "l2,2.\n");
    append_to_file(filename, "0.2,0.1;\n");
    append_to_file(filename, "0.8,0.9;");

    NN* nn = parse_nn(filename);
    ASSERT_EQ(nn->get_total_weights(), 2);
    ASSERT_EQ(nn->get_total_layers(), 3);
 
    Layer* l1 = nn->get_layer(0);
    ASSERT_EQ(l1->get_activation_name(), "none");
    ASSERT_TRUE(l1->is_input());
    ASSERT_EQ(l1->get_size(), 2);

    Layer* l2 = nn->get_layer(1);
    ASSERT_EQ(l2->get_activation_name(), "relu");
    ASSERT_FALSE(l2->is_input());
    ASSERT_EQ(l2->get_size(), 2);
    
    Layer* l3 = nn->get_layer(2);
    ASSERT_EQ(l3->get_activation_name(), "softmax");
    ASSERT_FALSE(l3->is_input());
    ASSERT_EQ(l3->get_size(), 2);

    Weights* w1 = nn->get_weight(0);
    Matrix* m1 = w1->get_weights();
    ASSERT_EQ(w1->get_width(), 2);
    ASSERT_EQ(w1->get_height(), 2);
    ASSERT_EQ(m1->get_position_value(0, 0), 0.3);
    ASSERT_EQ(m1->get_position_value(0, 1), 0.4);
    ASSERT_EQ(m1->get_position_value(1, 0), 0.5);
    ASSERT_EQ(m1->get_position_value(1, 1), 0.6);

  
    Weights* w2 = nn->get_weight(1);
    Matrix* m2 = w2->get_weights();
    ASSERT_EQ(w2->get_width(), 2);
    ASSERT_EQ(w2->get_height(), 2);
    ASSERT_EQ(m2->get_position_value(0, 0), 0.2);
    ASSERT_EQ(m2->get_position_value(0, 1), 0.1);
    ASSERT_EQ(m2->get_position_value(1, 0), 0.8);
    ASSERT_EQ(m2->get_position_value(1, 1), 0.9);
    delete nn;
  }

  

}
