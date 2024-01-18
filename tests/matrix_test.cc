#include <gtest/gtest.h>
#include <stdexcept>
#include "../matrix/matrix.h"

namespace {

  TEST(CreationTest, ZerosMatrix){
    unsigned int size = 2;
    Matrices::Matrix* matrix_obj = new Matrices::Matrix(size);
    matrix_obj->zeros();
    double ** matrix = matrix_obj->get_matrix();
    ASSERT_EQ(matrix[0][0], 0);
    ASSERT_EQ(matrix[0][1], 0);
    ASSERT_EQ(matrix[1][0], 0);
    ASSERT_EQ(matrix[1][1], 0);
  }

  TEST(UpdateTest, UpdateMatrixValue){
    unsigned int size = 2;
    unsigned int i = 1;
    unsigned int j = 1;
    double update_value = 10;  

    Matrices::Matrix* matrix_obj = new Matrices::Matrix(size);
    matrix_obj->zeros();
    matrix_obj->update_value(i, j, update_value);
    double ** matrix = matrix_obj->get_matrix();
    
    ASSERT_EQ(matrix[i][j], update_value);
  }

  TEST(UpdateTest, UpdateMatrixGreaterThanHeight){
    unsigned int size = 2;
    unsigned int i = 10;
    unsigned int j = 0;
    double update_value = 10;  

    Matrices::Matrix* matrix_obj = new Matrices::Matrix(size);
    matrix_obj->zeros();
    
    EXPECT_THROW({ 
      matrix_obj->update_value(i, j, update_value);
    }, std::invalid_argument);
  }
  
  TEST(UpdateTest, UpdateMatrixGreaterThanWidth){
    unsigned int size = 2;
    unsigned int i = 0;
    unsigned int j = 10;
    double update_value = 10;  

    Matrices::Matrix* matrix_obj = new Matrices::Matrix(size);
    matrix_obj->zeros();
    
    EXPECT_THROW({ 
      matrix_obj->update_value(i, j, update_value);
    }, std::invalid_argument);
  }
}
