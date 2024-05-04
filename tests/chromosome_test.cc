#include <gtest/gtest.h>
#include <vector>
#include "../genetic/gene.h"
#include "../genetic/chromosome.h"

using std::vector;
using Genetic::Chromosome;
using Genetic::Gene;

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

  TEST(UpdateTest, CopyGenesTest){
    Gene* genes = new Gene[3];
    Chromosome* chromosome = new Chromosome(3);
    chromosome->copy_genes(genes);
  
    ASSERT_NE(&genes[0], &chromosome->get_genes()[0]);
    ASSERT_NE(&genes[1], &chromosome->get_genes()[1]);
    ASSERT_NE(&genes[2], &chromosome->get_genes()[2]);
    
    ASSERT_EQ(genes[0].get_gene_value(), chromosome->get_genes()[0].get_gene_value());
    ASSERT_EQ(genes[1].get_gene_value(), chromosome->get_genes()[1].get_gene_value());
    ASSERT_EQ(genes[2].get_gene_value(), chromosome->get_genes()[2].get_gene_value());


    delete[] genes;
    delete chromosome;
  }

}
