#include <gtest/gtest.h>
#include <vector>
#include "../genetic/gene.h"
#include "../genetic/chromosome.h"

using std::vector;
using Chromosomes::Chromosome;
using Genes::Gene;

namespace {

  TEST(CreationTest, CreateDefaultChromosomeTest){
    Chromosome *chromosome = new Chromosome(2);
    ASSERT_EQ(chromosome->get_size(), 2);
    delete chromosome;
  }

  TEST(CreationTest, CreateChromosomeByGenesVectorTest){
    Gene* genes = new Gene[5];  
    Chromosome* chromosome = new Chromosome(genes, 5);
    ASSERT_EQ(chromosome->get_size(), 5);   

    delete chromosome;
  }
  
}
