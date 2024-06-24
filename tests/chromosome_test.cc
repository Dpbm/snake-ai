#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>
#include "../genetic/gene.h"
#include "../genetic/chromosome.h"

using std::invalid_argument;
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

  TEST(CreationTest, CreateChromosomeByGenesArrayTest){
    Gene* gene = new Gene[10];
    Chromosome ch{gene, 10};
    ASSERT_EQ(ch.get_genes(), gene);
    ASSERT_EQ(ch.get_size(), 10);
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

  TEST(ValuesTest, SliceChromossomeAtTheBeginingTest){
    Gene* genes = new Gene[10];
    Chromosome ch{genes, 10};
    Gene* slice = ch.slice(0, 3);
    ASSERT_NE(&slice[0], &genes[0]); 
    ASSERT_NE(&slice[1], &genes[1]); 
    ASSERT_NE(&slice[2], &genes[2]); 
    ASSERT_NE(&slice[3], &genes[3]);
    ASSERT_EQ(slice[0].get_gene_value(), genes[0].get_gene_value()); 
    ASSERT_EQ(slice[1].get_gene_value(), genes[1].get_gene_value()); 
    ASSERT_EQ(slice[2].get_gene_value(), genes[2].get_gene_value()); 
    delete slice;
  }
  
  TEST(ValuesTest, SliceChromossomeAtTheMiddleTest){
    Gene* genes = new Gene[10];
    Chromosome ch{genes, 10};
    Gene* slice = ch.slice(4, 7);
    ASSERT_NE(&slice[0], &genes[4]); 
    ASSERT_NE(&slice[1], &genes[5]); 
    ASSERT_NE(&slice[2], &genes[6]); 
    ASSERT_NE(&slice[3], &genes[7]); 
    ASSERT_EQ(slice[0].get_gene_value(), genes[4].get_gene_value()); 
    ASSERT_EQ(slice[1].get_gene_value(), genes[5].get_gene_value()); 
    ASSERT_EQ(slice[2].get_gene_value(), genes[6].get_gene_value()); 
    delete slice;
  }
  
  TEST(ValuesTest, SliceChromossomeAtTheEndTest){
    Gene* genes = new Gene[10];
    Chromosome ch{genes, 10};
    Gene* slice = ch.slice(7,10);
    ASSERT_NE(&slice[0], &genes[7]); 
    ASSERT_NE(&slice[1], &genes[8]); 
    ASSERT_NE(&slice[2], &genes[9]); 
    ASSERT_NE(&slice[3], &genes[10]); 
    ASSERT_EQ(slice[0].get_gene_value(), genes[7].get_gene_value()); 
    ASSERT_EQ(slice[1].get_gene_value(), genes[8].get_gene_value()); 
    ASSERT_EQ(slice[2].get_gene_value(), genes[9].get_gene_value()); 
  }
  
  TEST(ValuesTest, SliceStartGreaterThanTheEndValueTest){
    Gene* genes = new Gene[10];
    Chromosome ch{genes, 10};
    ASSERT_THROW({ ch.slice(5, 3); }, invalid_argument);
  }
  
  TEST(ValuesTest, SliceOutOfBoundsTest){
    Gene* genes = new Gene[10];
    Chromosome ch{genes, 10};
    ASSERT_THROW({ ch.slice(3, 11); }, invalid_argument);
    ASSERT_THROW({ ch.slice(11, 11); }, invalid_argument);
  }

  TEST(ValuesTest, SliceStartAndEndAsTheSamePositionTest){
    Gene* genes = new Gene[10];
    Chromosome ch{genes, 10};
    ASSERT_THROW({ ch.slice(3,3); }, invalid_argument);
  }
}
