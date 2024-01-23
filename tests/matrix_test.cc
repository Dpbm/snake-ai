#include <gtest/gtest.h>
#include <stdexcept>
#include "../matrix/matrix.h"

namespace {

  TEST(CreationTest, SquareMatrix){
    Matrices::Matrix* matrix = new Matrices::Matrix(3);
    
    matrix->update_value(0, 0, 1);
    matrix->update_value(0, 1, 1);
    matrix->update_value(0, 2, 1);
    matrix->update_value(1, 0, 2);
    matrix->update_value(1, 1, 2);
    matrix->update_value(1, 2, 2);
    matrix->update_value(2, 0, 3);
    matrix->update_value(2, 1, 3);
    matrix->update_value(2, 2, 3);

    ASSERT_EQ(matrix->get_position_value(0, 0), 1); 
    ASSERT_EQ(matrix->get_position_value(0, 1), 1); 
    ASSERT_EQ(matrix->get_position_value(0, 2), 1); 
    ASSERT_EQ(matrix->get_position_value(1, 0), 2); 
    ASSERT_EQ(matrix->get_position_value(1, 1), 2); 
    ASSERT_EQ(matrix->get_position_value(1, 2), 2); 
    ASSERT_EQ(matrix->get_position_value(2, 0), 3); 
    ASSERT_EQ(matrix->get_position_value(2, 1), 3); 
    ASSERT_EQ(matrix->get_position_value(2, 2), 3); 
    delete matrix;
  }

  TEST(CreationTest, DifferentSizeMatrix){
    Matrices::Matrix* matrix = new Matrices::Matrix(2, 3);
    
    matrix->update_value(0, 0, 1);
    matrix->update_value(0, 1, 1);
    matrix->update_value(1, 0, 2);
    matrix->update_value(1, 1, 2);
    matrix->update_value(2, 0, 3);
    matrix->update_value(2, 1, 3);

    ASSERT_EQ(matrix->get_position_value(0, 0), 1);
    ASSERT_EQ(matrix->get_position_value(0, 1), 1);
    ASSERT_EQ(matrix->get_position_value(1, 0), 2);
    ASSERT_EQ(matrix->get_position_value(1, 1), 2);
    ASSERT_EQ(matrix->get_position_value(2, 0), 3);
    ASSERT_EQ(matrix->get_position_value(2, 1), 3);

    delete matrix;
  }

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
    Matrices::Matrix* matrix = new Matrices::Matrix(2);
    matrix->zeros();
    
    EXPECT_THROW({ 
      matrix->update_value(2, 0, 10);
    }, std::invalid_argument);
    delete matrix;
  }
  
  TEST(UpdateTest, UpdateMatrixGreaterThanWidth){
    Matrices::Matrix* matrix = new Matrices::Matrix(2);
    matrix->zeros();
    
    EXPECT_THROW({ 
      matrix->update_value(2, 0, 10);
    }, std::invalid_argument);
    delete matrix;
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
  
  TEST(ValuesTest, GetPositionValuePositionGreaterThanHeight){
    Matrices::Matrix* matrix = new Matrices::Matrix(2);
    matrix->zeros();
    EXPECT_THROW({
      matrix->get_position_value(0, 2);
    }, std::invalid_argument);
    delete matrix;
  }

  TEST(ValuesTest, GetPositionValuePositionGreaterThanWidth){
    Matrices::Matrix* matrix = new Matrices::Matrix(2);
    matrix->zeros();
    EXPECT_THROW({
      matrix->get_position_value(2, 0);
    }, std::invalid_argument);
    delete matrix;
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

  TEST(ValuesTest, GetHeightTest){
    unsigned int size = 3;
    Matrices::Matrix* matrix = new Matrices::Matrix(size);
  
    ASSERT_EQ(matrix->get_height(), size);
    delete matrix;
  }
  
  TEST(ValuesTest, GetWidthTest){
    unsigned int size = 3;
    Matrices::Matrix* matrix = new Matrices::Matrix(size);
  
    ASSERT_EQ(matrix->get_width(), size);
    delete matrix;
  }

  
  TEST(ValuesTest, GetRowTest){
    Matrices::Matrix* matrix = new Matrices::Matrix(3, 2);
    
    matrix->zeros();
    matrix->update_value(0, 0, 1);
    matrix->update_value(0, 1, 2);
    matrix->update_value(0, 2, 3);

    double* row = matrix->get_row(0);

    ASSERT_EQ(row[0], 1);
    ASSERT_EQ(row[1], 2);
    ASSERT_EQ(row[2], 3);
    delete row;
    delete matrix;
  }
  
  TEST(ValuesTest, GetColumnTest){
    Matrices::Matrix* matrix = new Matrices::Matrix(2, 3);
    
    matrix->zeros();
    matrix->update_value(0, 1, 1);
    matrix->update_value(1, 1, 2);
    matrix->update_value(2, 1, 3);

    double* column = matrix->get_column(1);

    ASSERT_EQ(column[0], 1);
    ASSERT_EQ(column[1], 2);
    ASSERT_EQ(column[2], 3);
    delete column;
    delete matrix;
  }

  TEST(ValuesTest, DotProductTest){
    Matrices::Matrix* matrix_1 = new Matrices::Matrix(3, 1);
    Matrices::Matrix* matrix_2 = new Matrices::Matrix(2, 3);
  
    matrix_1->update_value(0, 0, 1);
    matrix_1->update_value(0, 1, 2);
    matrix_1->update_value(0, 2, 3);
    
    matrix_2->update_value(0, 0, 1);
    matrix_2->update_value(0, 1, 2);
    matrix_2->update_value(1, 0, 1);
    matrix_2->update_value(1, 1, 2);
    matrix_2->update_value(2, 0, 1);
    matrix_2->update_value(2, 1, 2);

    Matrices::Matrix result = (*matrix_1) * (*matrix_2);
    
    ASSERT_EQ(result.get_width(), 2);
    ASSERT_EQ(result.get_height(), 1);
    ASSERT_EQ(result.get_position_value(0, 0), 6);
    ASSERT_EQ(result.get_position_value(0, 1), 12);

    delete matrix_1;
    delete matrix_2;
  }
  
  TEST(ValuesTest, DotProductErrorTest){
    Matrices::Matrix* matrix_1 = new Matrices::Matrix(3, 1);
    Matrices::Matrix* matrix_2 = new Matrices::Matrix(2, 5);
    EXPECT_THROW({ 
      (*matrix_1) * (*matrix_2); 
    }, std::invalid_argument);
    delete matrix_1;
    delete matrix_2;
  }
}
