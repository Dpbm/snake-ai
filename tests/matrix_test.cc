#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../matrix/matrix.h"
#include "../genetic/gene.h"

using ::testing::AllOf;
using ::testing::Ge;
using ::testing::Le;
using Genes::Gene;

namespace {

  TEST(CreationTest, SquareMatrix){
    Matrices::Matrix<double>* matrix = new Matrices::Matrix<double>(3);
    
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
    Matrices::Matrix<double>* matrix = new Matrices::Matrix<double>(2, 3);
    
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
    Matrices::Matrix<double>* matrix = new Matrices::Matrix<double>(2);
    matrix->map_to_a_single_value(0);
  
    ASSERT_EQ(matrix->get_position_value(0, 0), 0);
    ASSERT_EQ(matrix->get_position_value(0, 1), 0);
    ASSERT_EQ(matrix->get_position_value(1, 0), 0);
    ASSERT_EQ(matrix->get_position_value(1, 1), 0);
    delete matrix;
  }

  TEST(UpdateTest, UpdateMatrixValue){
    Matrices::Matrix<double>* matrix = new Matrices::Matrix<double>(2);
    
    matrix->map_to_a_single_value(0);
    matrix->update_value(1, 1, 10);
    
    ASSERT_EQ(matrix->get_position_value(1, 1), 10);
    delete matrix;
  }

  TEST(UpdateTest, UpdateMatrixGreaterThanHeight){
    Matrices::Matrix<double>* matrix = new Matrices::Matrix<double>(2);
    matrix->map_to_a_single_value(0);
    
    EXPECT_THROW({ 
      matrix->update_value(2, 0, 10);
    }, std::invalid_argument);
    delete matrix;
  }
  
  TEST(UpdateTest, UpdateMatrixGreaterThanWidth){
    Matrices::Matrix<double>* matrix = new Matrices::Matrix<double>(2);
    matrix->map_to_a_single_value(0);
    
    EXPECT_THROW({ 
      matrix->update_value(2, 0, 10);
    }, std::invalid_argument);
    delete matrix;
  }

  TEST(ValuesTest, GetPositionValueTest){
    Matrices::Matrix<double>* matrix = new Matrices::Matrix<double>(2);
    matrix->map_to_a_single_value(0);

    matrix->update_value(1, 1, 5);
    ASSERT_EQ(matrix->get_position_value(1, 1), 5);
    delete matrix;
  }
  
  TEST(ValuesTest, GetPositionValuePositionGreaterThanHeight){
    Matrices::Matrix<double>* matrix = new Matrices::Matrix<double>(2);

    matrix->map_to_a_single_value(0);
  
    EXPECT_THROW({
      matrix->get_position_value(0, 2);
    }, std::invalid_argument);
    delete matrix;
  }

  TEST(ValuesTest, GetPositionValuePositionGreaterThanWidth){
    Matrices::Matrix<double>* matrix = new Matrices::Matrix<double>(2);
    matrix->map_to_a_single_value(0);

    EXPECT_THROW({
      matrix->get_position_value(2, 0);
    }, std::invalid_argument);
    delete matrix;
  }

  TEST(ValuesTest, OverWriteMatrixTest){
    Matrices::Matrix<double>* matrix_1 = new Matrices::Matrix<double>(2);
    Matrices::Matrix<double>* matrix_2 = new Matrices::Matrix<double>(2);
    matrix_1->map_to_a_single_value(0);
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
    Matrices::Matrix<double>* matrix = new Matrices::Matrix<double>(3);
    ASSERT_EQ(matrix->get_height(), 3);
    delete matrix;
  }
  
  TEST(ValuesTest, GetWidthTest){
    Matrices::Matrix<double>* matrix = new Matrices::Matrix<double>(3);
    ASSERT_EQ(matrix->get_width(), 3);
    delete matrix;
  }

  
  TEST(ValuesTest, GetRowTest){
    Matrices::Matrix<double>* matrix = new Matrices::Matrix<double>(3, 2);
    
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
    Matrices::Matrix<double>* matrix = new Matrices::Matrix<double>(2, 3);
    
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
    Matrices::Matrix<double>* matrix_1 = new Matrices::Matrix<double>(3, 1);
    Matrices::Matrix<Gene*>* matrix_2 = new Matrices::Matrix<Gene*>(2, 3);
  
    matrix_1->update_value(0, 0, 1);
    matrix_1->update_value(0, 1, 2);
    matrix_1->update_value(0, 2, 3);
    
    matrix_2->update_value(0, 0, 1);
    matrix_2->update_value(0, 1, 2);
    matrix_2->update_value(1, 0, 1);
    matrix_2->update_value(1, 1, 2);
    matrix_2->update_value(2, 0, 1);
    matrix_2->update_value(2, 1, 2);

    Matrices::Matrix<double> result = (*matrix_1) * (*matrix_2);
    
    ASSERT_EQ(result.get_width(), 2);
    ASSERT_EQ(result.get_height(), 1);
    ASSERT_EQ(result.get_position_value(0, 0), 6);
    ASSERT_EQ(result.get_position_value(0, 1), 12);
    delete matrix_1;
    delete matrix_2;
  }
  
  TEST(ValuesTest, DotProductErrorTest){
    Matrices::Matrix<double>* matrix_1 = new Matrices::Matrix<double>(3, 1);
    Matrices::Matrix<Gene*>* matrix_2 = new Matrices::Matrix<Gene*>(2, 5);
    EXPECT_THROW({ 
      (*matrix_1) * (*matrix_2); 
    }, std::invalid_argument);
    delete matrix_1;
    delete matrix_2;
  }

  TEST(UpdateTest, TransposeTest){
    Matrices::Matrix<double>* matrix = new Matrices::Matrix<double>(2, 1);
    matrix->map_to_a_single_value(0);
    matrix->transpose();
    
    ASSERT_EQ(matrix->get_width(), 1);
    ASSERT_EQ(matrix->get_height(), 2);
    ASSERT_EQ(matrix->get_position_value(0, 0), 0);
    ASSERT_EQ(matrix->get_position_value(1, 0), 0);
    EXPECT_THROW({ matrix->get_position_value(0, 1); }, std::invalid_argument);
    delete matrix;
  }
}
