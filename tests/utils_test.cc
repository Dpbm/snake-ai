#include <cstdint>
#include <gtest/gtest.h>
#include <stdexcept>
#include "../helpers/utils.h"

using std::invalid_argument;
using Utils::distance;
using Utils::parse_nn_arch;

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
}
