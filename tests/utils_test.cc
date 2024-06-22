#include <cstdint>
#include <fstream>
#include <gtest/gtest.h>
#include <stdexcept>
#include "../helpers/utils.h"
#include "../matrix/matrix.h"

using std::getline;
using std::ifstream;
using std::invalid_argument;
using Matrices::Matrix;
using Utils::distance;
using Utils::parse_nn_arch;
using Utils::parse_weights_head;
using Utils::parse_layers_sizes;
using Utils::parse_activations;
using Utils::parse_row;
using Utils::create_file;
using Utils::append_to_file;

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
}
