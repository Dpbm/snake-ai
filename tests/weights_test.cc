#include <stdexcept>
#include <gtest/gtest.h>
#include <fstream>
#include "../machine/weights.h"
#include "../matrix/matrix.h"
#include "../genetic/gene.h"

using std::ifstream;
using NNWeights::Weights;
using Matrices::Matrix;
using Genes::Gene;

namespace {
  TEST(CreationTest, CreateWeightsTest){
    Weights* weights = new Weights(2, 3);
    ASSERT_EQ(weights->get_width(), 2);
    ASSERT_EQ(weights->get_height(), 3);
    ASSERT_EQ(weights->get_weights()->get_width(), 2);
    ASSERT_EQ(weights->get_weights()->get_height(), 3);
    delete weights;
  }

  TEST(UpdateTest, LoadWeightsTest){
    Weights* weights = new Weights(2, 3);
    Matrix<Gene>* matrix = new Matrix<Gene>(2, 3);
    matrix->map_to_a_single_value(0);
    weights->load_weights(matrix);
    ASSERT_EQ(weights->get_weights(), matrix);
    ASSERT_EQ(weights->get_width(), 2);
    ASSERT_EQ(weights->get_height(), 3);
    ASSERT_EQ(weights->get_weights()->get_width(), 2);
    ASSERT_EQ(weights->get_weights()->get_height(), 3);
    delete weights;
  }

  TEST(ValuesTest, SaveWeightsToFileTest){
    Weights* weights = new Weights(2, 2);
    weights->save_weights("test_save.wg");
    ifstream file("test_save.wg");
    ASSERT_EQ(file.good(), true);
    file.close();
    delete weights;
  }
}
