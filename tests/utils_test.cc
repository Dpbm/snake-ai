#include <gtest/gtest.h>
#include "../helpers/utils.h"
#include "../helpers/constants.h"

using Utils::get_angle;

namespace {
  
  TEST(ValueTest, getAngle0Test){
    ASSERT_DOUBLE_EQ(get_angle(5, 7, 5, 10), 0);
    ASSERT_DOUBLE_EQ(get_angle(5, 5, 5, 5), 0);
    ASSERT_DOUBLE_EQ(get_angle(5, 10, 5, 10), 0);
  }

  TEST(ValueTest, getAngle90Test){
    ASSERT_DOUBLE_EQ(get_angle(5, 10, 3, 10), PI/2);
    ASSERT_DOUBLE_EQ(get_angle(10, 10, 5, 10), PI/2);
  }
  
  TEST(ValueTest, getAngle180Test){
    ASSERT_DOUBLE_EQ(get_angle(5, 10, 5, 6), PI);
  }
  
  TEST(ValueTest, getAngle270Test){
    ASSERT_DOUBLE_EQ(get_angle(5, 10, 7, 10), (3*PI)/2);
  }

  TEST(ValueTest, GetAngleFirstSector){
    ASSERT_DOUBLE_EQ(get_angle(10, 10, 5, 15), PI/4);
  }
  
  TEST(ValueTest, GetAngleSecondSector){
    ASSERT_DOUBLE_EQ(get_angle(10, 10, 5, 5), (3*PI)/4);
  }
  
  TEST(ValueTest, GetAngleThirdSector){
    ASSERT_DOUBLE_EQ(get_angle(10, 10, 15, 5), (5*PI)/4);
  }
  
  TEST(ValueTest, GetAngleFourthSector){
    ASSERT_DOUBLE_EQ(get_angle(10, 10, 15, 15), (7*PI)/4);
  }
}
