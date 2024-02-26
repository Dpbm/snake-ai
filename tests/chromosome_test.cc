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
  
  TEST(ValuesTest, SliceTest){
    Chromosome *chromosome = new Chromosome(3, 100);
    Gene *slice = chromosome->slice(1, 2);
    
    ASSERT_EQ(slice[0].get_gene_value(), chromosome->get_genes()[1].get_gene_value());
    ASSERT_EQ(slice[1].get_gene_value(), chromosome->get_genes()[2].get_gene_value());
    
    delete chromosome;
    delete slice;
  }  

  TEST(ValuesTest, SliceOutOfSuperiorBoundTest){
    Chromosome *chromosome = new Chromosome(2, 100);
    EXPECT_THROW({
      chromosome->slice(0, 2);
    }, std::invalid_argument);
    delete chromosome;
  }

  TEST(ValuesTest, SliceInvertedArgumentsTest){
    Chromosome *chromosome = new Chromosome(2, 100);
    EXPECT_THROW({
      chromosome->slice(1, 0);
    }, std::invalid_argument);
    delete chromosome;
  }
  
  TEST(ValuesTest, CrossoverDisplacedFromStartTest){
    Gene *genes1 = new Gene[4];
    for(unsigned int i = 0; i < 4; i++)
      genes1[i].set_gene_value(1);
    Chromosome* chromosome = new Chromosome(genes1, 4, 100);
  
    Gene *genes2 = new Gene[3];
    for(unsigned int i = 0; i < 3; i++)
      genes2[i].set_gene_value(0);

    chromosome->crossover(1, 3, genes2);

    ASSERT_EQ(chromosome->get_genes()[0].get_gene_value(), 1);
    ASSERT_EQ(chromosome->get_genes()[1].get_gene_value(), 0);
    ASSERT_EQ(chromosome->get_genes()[2].get_gene_value(), 0);
    ASSERT_EQ(chromosome->get_genes()[3].get_gene_value(), 0);
    
    delete chromosome;
  }

  TEST(ValuesTest, CrossoverDisplacedFromEndTest){
    Gene *genes1 = new Gene[4];
    for(unsigned int i = 0; i < 4; i++)
      genes1[i].set_gene_value(1);
    Chromosome* chromosome = new Chromosome(genes1, 4, 100);
    
  
    Gene *genes2 = new Gene[3];
    for(unsigned int i = 0; i < 3; i++)
      genes2[i].set_gene_value(0);

    chromosome->crossover(0, 2, genes2);

    ASSERT_EQ(chromosome->get_genes()[0].get_gene_value(), 0);
    ASSERT_EQ(chromosome->get_genes()[1].get_gene_value(), 0);
    ASSERT_EQ(chromosome->get_genes()[2].get_gene_value(), 0);
    ASSERT_EQ(chromosome->get_genes()[3].get_gene_value(), 1);
    
    delete chromosome;
  }  
  
  TEST(ValuesTest, CrossoverInTheMiddleTest){
    Gene *genes1 = new Gene[4];
    for(unsigned int i = 0; i < 4; i++)
      genes1[i].set_gene_value(1);
    Chromosome* chromosome = new Chromosome(genes1, 4, 100);
    
  
    Gene *genes2 = new Gene[2];
    for(unsigned int i = 0; i < 2; i++)
      genes2[i].set_gene_value(0);

    chromosome->crossover(1,2, genes2);

    ASSERT_EQ(chromosome->get_genes()[0].get_gene_value(), 1);
    ASSERT_EQ(chromosome->get_genes()[1].get_gene_value(), 0);
    ASSERT_EQ(chromosome->get_genes()[2].get_gene_value(), 0);
    ASSERT_EQ(chromosome->get_genes()[3].get_gene_value(), 1);
    
    delete chromosome;
  }

  
  TEST(ValuesTest, CrossoverWithTheWholeChromosomeTest){
    Gene *genes1 = new Gene[4];
    for(unsigned int i = 0; i < 4; i++)
      genes1[i].set_gene_value(1);
    Chromosome* chromosome = new Chromosome(genes1, 4, 100);
  
    Gene *genes2 = new Gene[4];
    for(unsigned int i = 0; i < 4; i++)
      genes2[i].set_gene_value(0);

    chromosome->crossover(0,3, genes2);

    ASSERT_EQ(chromosome->get_genes()[0].get_gene_value(), 0);
    ASSERT_EQ(chromosome->get_genes()[1].get_gene_value(), 0);
    ASSERT_EQ(chromosome->get_genes()[2].get_gene_value(), 0);
    ASSERT_EQ(chromosome->get_genes()[3].get_gene_value(), 0);
    
    delete chromosome;
  }
  
  TEST(UpdateTest, UpdatePointsTest){
    Chromosome *chromosome = new Chromosome(1, 1);
    chromosome->update_points(-1);
    ASSERT_EQ(chromosome->get_points(), 0);
    delete chromosome;
  }
}
