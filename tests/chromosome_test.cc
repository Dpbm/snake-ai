#include <gtest/gtest.h>
#include <vector>
#include "../genetic/gene.h"
#include "../genetic/chromosome.h"

using std::vector;
using Chromosomes::Chromosome;
using Genes::Gene;

namespace {

  TEST(CreationTest, CreateDefaultChromosomeTest){
    Chromosome *chromosome = new Chromosome(2, 100);
    ASSERT_EQ(chromosome->get_size(), 2);
    ASSERT_EQ(chromosome->get_points(), 100);
    delete chromosome;
  }

  TEST(CreationTest, CreateChromosomeByGenesVectorTest){
    Gene* genes = new Gene[5];  
    Chromosome* chromosome = new Chromosome(genes, 5, 100);
    ASSERT_EQ(chromosome->get_size(), 5);   

    delete chromosome;
  }
  
  TEST(UpdateTest, UpdatePointsTest){
    Chromosome *chromosome = new Chromosome(1, 1);
    chromosome->update_points(-1);
    ASSERT_EQ(chromosome->get_points(), 0);
    delete chromosome;
  }
}
