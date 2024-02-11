#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdexcept>
#include "../genetic/gene.h"

using ::testing::AllOf;
using ::testing::Ge;
using ::testing::Le;
using std::invalid_argument;
using Genes::Gene;

namespace {
  TEST(CreationTest, CreateGeneTest){
    Gene *gene = new Gene();
    ASSERT_THAT(gene->get_gene_value(), AllOf(Ge(-1), Le(1)));
    delete gene;
  }

  TEST(UpdateTest, SetGeneValueTest){
    Gene *gene = new Gene();
    gene->set_gene_value(3);
    ASSERT_EQ(gene->get_gene_value(), 3);
    delete gene;
  }

  TEST(UpdateTest, MutationLesserThanZeroRateTest){
    Gene *gene = new Gene();
    EXPECT_THROW({ gene->mutate(-1); }, invalid_argument);
    delete gene;
  } 
  
  TEST(UpdateTest, MutationGreaterThanOneRateTest){
    Gene *gene = new Gene();
    EXPECT_THROW({ gene->mutate(2); }, invalid_argument);
    delete gene;
  }

  
  TEST(UpdateTest, MostProbableMutationTest){
    Gene *gene = new Gene();
    gene->set_gene_value(100);
    gene->mutate(1);
    ASSERT_NE(gene->get_gene_value(), 100);
    delete gene;
  } 
  
  TEST(UpdateTest, LestProbableMutationTest){
    Gene *gene = new Gene();
    gene->set_gene_value(100);
    gene->mutate(0);
    ASSERT_EQ(gene->get_gene_value(), 100);
    delete gene;
  }

  TEST(ValuesTest, CopyGeneTest){
    Gene *gene = new Gene();
    gene->set_gene_value(100);
    
    Gene *copy_gene = gene->copy();
    
    ASSERT_EQ(gene->get_gene_value(), copy_gene->get_gene_value());
    ASSERT_NE(gene, copy_gene);

    delete gene;
    delete copy_gene;
  }

  TEST(UpdateTest, AssignOperatorTest){
    Gene* gene = new Genes::Gene();
    ASSERT_NE(gene->get_gene_value(), 10);
    (*gene) = 10.0;
    ASSERT_EQ(gene->get_gene_value(), 10);
    delete gene;
  }
  
  TEST(ValueTest, AdditionOperatorTest){
    Gene* gene = new Genes::Gene();
    (*gene) = 2.0;
    ASSERT_EQ((*gene)+4.0, 6);
    delete gene;
  }

  TEST(ValuesTest, ProductOperatorTest){
    Gene* gene = new Genes::Gene();
    (*gene) = 2.0;
    ASSERT_EQ((*gene)*3.0, 6);
    delete gene;
  } 
}

