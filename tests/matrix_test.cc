#include <gtest/gtest.h>
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
}
