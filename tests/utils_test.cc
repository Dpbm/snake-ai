#include <cstdint>
#include <gtest/gtest.h>
#include <stdexcept>
#include "../helpers/utils.h"
#include "../matrix/matrix.h"


using std::invalid_argument;
using Matrices::Matrix;
using Utils::distance;
using Utils::parse_nn_arch;
using Utils::parse_weights_head;

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
  
}
