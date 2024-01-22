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
    delete matrix;
    delete matrix_obj;
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
    delete matrix;
    delete matrix_obj;
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
    delete matrix_obj;
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
    delete matrix_obj;
  }

  TEST(ValuesTest, GetPositionValueTest){
    unsigned int size = 2;
    Matrices::Matrix* matrix_obj = new Matrices::Matrix(size);
    matrix_obj->zeros();

    unsigned int i = 1;
    unsigned int j = 1;
    double value = 5;
    matrix_obj->update_value(i, j, value);
    ASSERT_EQ(matrix_obj->get_position_value(i, j), value);

    delete matrix_obj;
  }

  TEST(ValuesTest, CopyMatrixTest){
    unsigned int size = 2;
    Matrices::Matrix* matrix_obj = new Matrices::Matrix(size);
    matrix_obj->zeros();
    matrix_obj->update_value(0, 0, 1);
    matrix_obj->update_value(0, 1, 2);
    matrix_obj->update_value(1, 0, 3);
    matrix_obj->update_value(1, 1, 4);
    
    Matrices::Matrix clone_matrix = matrix_obj->copy();

    ASSERT_EQ(matrix_obj->get_position_value(0, 0), 1);
    ASSERT_EQ(matrix_obj->get_position_value(0, 1), 2);
    ASSERT_EQ(matrix_obj->get_position_value(1, 0), 3);
    ASSERT_EQ(matrix_obj->get_position_value(1, 1), 4);
    delete matrix_obj;
  }

  TEST(ValuesTest, MultiplyMatrixByScalarTest){
    unsigned int size = 2;
    Matrices::Matrix* matrix_obj = new Matrices::Matrix(size);
    matrix_obj->update_value(0, 0, 1);
    matrix_obj->update_value(0, 1, 2);
    matrix_obj->update_value(1, 0, 3);
    matrix_obj->update_value(1, 1, 4);
    
    Matrices::Matrix multiplication_result = (*matrix_obj)*5;

    ASSERT_EQ(multiplication_result.get_position_value(0, 0), 5);
    ASSERT_EQ(multiplication_result.get_position_value(0, 1), 10);
    ASSERT_EQ(multiplication_result.get_position_value(1, 0), 15);
    ASSERT_EQ(multiplication_result.get_position_value(1, 1), 20);
    delete matrix_obj;
  }
  
  TEST(ValuesTest, OverWriteMatrixTest){
    unsigned int size = 2;
    Matrices::Matrix* matrix_1 = new Matrices::Matrix(size);
    Matrices::Matrix* matrix_2 = new Matrices::Matrix(size);
    matrix_1->zeros();
    matrix_2->update_value(0, 0, 1);
    matrix_2->update_value(0, 1, 2);
    matrix_2->update_value(1, 0, 3);
    matrix_2->update_value(1, 1, 4);
    *matrix_1 = *matrix_2;
    
    ASSERT_EQ(matrix_1->get_position_value(0, 0), 1);
    ASSERT_EQ(matrix_1->get_position_value(0, 1), 2);
    ASSERT_EQ(matrix_1->get_position_value(1, 0), 3);
    ASSERT_EQ(matrix_1->get_position_value(1, 1), 4);
    delete matrix_1;
    delete matrix_2;
  } 
}
  
