#include <vector>
#include <gtest/gtest.h>
#include "../genetic/gene.h"
#include "../machine/weights.h"
#include "../helpers/utils.h"

using std::vector;
using Genes::Gene;
using NNWeights::Weights;
using Utils::weights_to_genes_vector;

namespace {
  TEST(ValuesTest, WeightsToGenesVectorTest){
    Weights* weights = new Weights(2, 1);
    vector<Gene*> *genes =  weights_to_genes_vector(weights->get_weights());
    
    ASSERT_EQ(genes->size(), 2);
    ASSERT_EQ(genes->at(0), &weights->get_weights()->get_matrix()[0][0]);
    ASSERT_EQ(genes->at(1), &weights->get_weights()->get_matrix()[0][1]);
  }
}
