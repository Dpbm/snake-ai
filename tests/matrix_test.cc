#include <gtest/gtest.h>
#include "../matrix/matrix.h"
#include "../genetic/gene.h"

using Genes::Gene;
using Matrices::Matrix;

namespace {
  TEST(CreationTest, SquareMatrixTest){
    Matrix<double>* matrix = new Matrix<double>(3);
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

  TEST(CreationTest, DifferentSizeMatrixTest){
    Matrix<double>* matrix = new Matrix<double>(2, 3);
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

  TEST(CreationTest, MapToASingleValueTest){
    Matrix<double>* matrix = new Matrix<double>(2);
    matrix->map_to_a_single_value(3);
    ASSERT_EQ(matrix->get_position_value(0, 0), 3);
    ASSERT_EQ(matrix->get_position_value(0, 1), 3);
    ASSERT_EQ(matrix->get_position_value(1, 0), 3);
    ASSERT_EQ(matrix->get_position_value(1, 1), 3);
    delete matrix;
  }

  TEST(UpdateTest, UpdateMatrixValueTest){
    Matrix<double>* matrix = new Matrix<double>(2);
    matrix->map_to_a_single_value(0);
    matrix->update_value(1, 1, 10);
    
    ASSERT_EQ(matrix->get_position_value(0, 0), 0);
    ASSERT_EQ(matrix->get_position_value(0, 1), 0);
    ASSERT_EQ(matrix->get_position_value(1, 0), 0);
    ASSERT_EQ(matrix->get_position_value(1, 1), 10);
    delete matrix;
  }

  TEST(UpdateTest, UpdateMatrixGreaterThanHeightTest){
    Matrix<double>* matrix = new Matrix<double>(2);
    matrix->map_to_a_single_value(0);
    EXPECT_THROW({ 
      matrix->update_value(2, 0, 10);
    }, std::invalid_argument);
    delete matrix;
  }
  
  TEST(UpdateTest, UpdateMatrixGreaterThanWidthTest){
    Matrix<double>* matrix = new Matrix<double>(2);
    matrix->map_to_a_single_value(0);
    EXPECT_THROW({ 
      matrix->update_value(2, 0, 10);
    }, std::invalid_argument);
    delete matrix;
  }

  TEST(ValuesTest, GetPositionValueTest){
    Matrix<double>* matrix = new Matrix<double>(2);
    matrix->map_to_a_single_value(0);

    matrix->update_value(1, 1, 5);
    ASSERT_EQ(matrix->get_position_value(1, 1), 5);
    delete matrix;
  }
  
  TEST(ValuesTest, GetPositionValuePositionGreaterThanHeightTest){
    Matrix<double>* matrix = new Matrix<double>(2);
    matrix->map_to_a_single_value(0);
    EXPECT_THROW({
      matrix->get_position_value(0, 2);
    }, std::invalid_argument);
    delete matrix;
  }

  TEST(ValuesTest, GetPositionValuePositionGreaterThanWidthTest){
    Matrix<double>* matrix = new Matrix<double>(2);
    matrix->map_to_a_single_value(0);
    EXPECT_THROW({
      matrix->get_position_value(2, 0);
    }, std::invalid_argument);
    delete matrix;
  }

  TEST(ValuesTest, GetHeightTest){
    Matrix<double>* matrix = new Matrix<double>(3);
    ASSERT_EQ(matrix->get_height(), 3);
    delete matrix;
  }
  
  TEST(ValuesTest, GetWidthTest){
    Matrix<double>* matrix = new Matrix<double>(3);
    ASSERT_EQ(matrix->get_width(), 3);
    delete matrix;
  }

  
  TEST(ValuesTest, GetRowTest){
    Matrix<double>* matrix = new Matrix<double>(3, 2);
    matrix->map_to_a_single_value(0);
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
    Matrix<double>* matrix = new Matrix<double>(2, 3);
    matrix->map_to_a_single_value(0);
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
    Matrix<double>* matrix_1 = new Matrix<double>(3, 1);
    Matrix<Gene>* matrix_2 = new Matrix<Gene>(2, 3);
  
    matrix_1->update_value(0, 0, 1);
    matrix_1->update_value(0, 1, 2);
    matrix_1->update_value(0, 2, 3);
    
    matrix_2->update_value(0, 0, 1);
    matrix_2->update_value(0, 1, 2);
    matrix_2->update_value(1, 0, 1);
    matrix_2->update_value(1, 1, 2);
    matrix_2->update_value(2, 0, 1);
    matrix_2->update_value(2, 1, 2);

    Matrix<double>* result = (*matrix_1) * (*matrix_2);
    
    ASSERT_EQ(result->get_width(), 2);
    ASSERT_EQ(result->get_height(), 1);
    ASSERT_EQ(result->get_position_value(0, 0), 6);
    ASSERT_EQ(result->get_position_value(0, 1), 12);
    ASSERT_NE(result, matrix_1);
    delete matrix_1;
    delete matrix_2;
    delete result;
  }
  
  TEST(ValuesTest, DotProductErrorTest){
    Matrix<double>* matrix_1 = new Matrix<double>(3, 1);
    Matrix<Gene>* matrix_2 = new Matrix<Gene>(2, 5);
    EXPECT_THROW({ 
      (*matrix_1) * (*matrix_2); 
    }, std::invalid_argument);
    delete matrix_1;
    delete matrix_2;
  }

  TEST(UpdateTest, TransposeTest){
    Matrix<double>* matrix = new Matrix<double>(2, 1);
    matrix->map_to_a_single_value(0);
    matrix->transpose();
    
    ASSERT_EQ(matrix->get_width(), 1);
    ASSERT_EQ(matrix->get_height(), 2);
    ASSERT_EQ(matrix->get_position_value(0, 0), 0);
    ASSERT_EQ(matrix->get_position_value(1, 0), 0);
    EXPECT_THROW({ matrix->get_position_value(0, 1); }, std::invalid_argument);
    delete matrix;
  }

  TEST(UpdateTest, UpdateGeneMatrixValuesTest){
    Matrix<Gene>* matrix = new Matrix<Gene>(1);
    matrix->update_value(0, 0, 10);
    ASSERT_EQ(matrix->get_position_value(0, 0), 10);
    delete matrix; 
  }
}
