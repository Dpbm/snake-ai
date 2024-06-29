#include <gtest/gtest.h>
#include "../helpers/exceptions.h"

using Utils::FileNotFound;
using Utils::InvalidValues;

namespace {
  TEST(ValueTest, TestFileNotFoundTest){
    try{
      throw FileNotFound();
    }catch(FileNotFound error){
      ASSERT_EQ(error.what(), "File Not Found!");
    }
  }
  
  TEST(ValueTest, InvalidValuesTest){
    try{
      throw InvalidValues();
    }catch(InvalidValues error){
      ASSERT_EQ(error.what(), "You haven't set the intern class values before doing the operation!");
    }
  }
}
