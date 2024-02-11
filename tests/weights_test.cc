#include <stdexcept>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fstream>
#include "../machine/weights.h"
#include "../matrix/matrix.h"
#include "../genetic/gene.h"

using ::testing::AllOf;
using ::testing::Ge;
using ::testing::Le;
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

  TEST(ValuesTest, EnsureRandomGeneValuesTest){
    Weights* weights = new Weights(1, 2);
    ASSERT_THAT(weights->get_weights()->get_position_value(0, 0), AllOf(Ge(-1), Le(1)));
    ASSERT_THAT(weights->get_weights()->get_position_value(1, 0), AllOf(Ge(-1), Le(1)));
    delete weights;
  }
}
