#include <gtest/gtest.h>
#include "../genetic/chromosome.h"
#include <stdexcept>
#include <vector>
#include "../genetic/gene.h"


namespace {

  TEST(CreationTest, CreateDefaultChromosomeTest){
    Chromosomes::Chromosome *chromosome = new Chromosomes::Chromosome(2, 100);
    std::vector<Genes::Gene*> *genes = chromosome->get_genes();
    ASSERT_EQ(genes->size(), 2);
    ASSERT_EQ(chromosome->get_points(), 100);
    delete chromosome;
  }

  
  TEST(CreationTest, CreateChromosomeWithoutGenesTest){
    Chromosomes::Chromosome *chromosome = new Chromosomes::Chromosome(100);
    std::vector<Genes::Gene*> *genes = chromosome->get_genes();
    ASSERT_EQ(genes->size(), 0);
    ASSERT_EQ(chromosome->get_points(), 100);
    delete chromosome;
  }


  TEST(CreationTest, SetGenesTest){
    Chromosomes::Chromosome *chromosome = new Chromosomes::Chromosome(100);
    std::vector<Genes::Gene*> *chromosome_genes = chromosome->get_genes();  
    ASSERT_EQ(chromosome_genes->size(), 0);
    
    std::vector<Genes::Gene*> *genes = new std::vector<Genes::Gene*>;  
    for(unsigned int i = 0; i < 5; i++)
      genes->push_back(new Genes::Gene);
   
    chromosome->set_genes(genes);
    chromosome_genes = chromosome->get_genes();  
    ASSERT_EQ(chromosome_genes->size(), genes->size());   

    delete chromosome;
  }
  
  TEST(ValuesTest, SliceTest){
    Chromosomes::Chromosome *chromosome = new Chromosomes::Chromosome(3, 100);
    std::vector<Genes::Gene*> *chromosome_genes = chromosome->get_genes();  

  std::vector<Genes::Gene*> *genes_manual = new std::vector<Genes::Gene*>;
    genes_manual->push_back(chromosome_genes->at(1));
    genes_manual->push_back(chromosome_genes->at(2));

    std::vector<Genes::Gene*> *slice = chromosome->slice(1, 2);
    ASSERT_EQ(slice->size(), 2);
    ASSERT_EQ(slice->at(0)->get_gene_value(), genes_manual->at(0)->get_gene_value());
    ASSERT_EQ(slice->at(1)->get_gene_value(), genes_manual->at(1)->get_gene_value());
    
    
    ASSERT_NE(slice->at(0), genes_manual->at(0));
    ASSERT_NE(slice->at(1), genes_manual->at(1));
    delete chromosome;
    delete slice;
  }  

  TEST(ValuesTest, SliceWithNoGenesTest){
    Chromosomes::Chromosome *chromosome = new Chromosomes::Chromosome(100);
    EXPECT_THROW({
      chromosome->slice(1, 3);
    }, std::invalid_argument);
    delete chromosome;
  }
  
  TEST(ValuesTest, SliceOutOfSuperiorBoundTest){
    Chromosomes::Chromosome *chromosome = new Chromosomes::Chromosome(2, 100);
    EXPECT_THROW({
      chromosome->slice(0, 2);
    }, std::invalid_argument);
    delete chromosome;
  }

  TEST(ValuesTest, SliceInvertedArgumentsTest){
    Chromosomes::Chromosome *chromosome = new Chromosomes::Chromosome(2, 100);
    EXPECT_THROW({
      chromosome->slice(1, 0);
    }, std::invalid_argument);
    delete chromosome;
  }
  
  TEST(ValuesTest, CrossoverInvalidSizeTest){
    Chromosomes::Chromosome *chromosome = new Chromosomes::Chromosome(4, 100);
    std::vector<Genes::Gene*>* slice = chromosome->slice(1,2); 
    
    EXPECT_THROW({
      chromosome->crossover(0, 3, slice);
    }, std::invalid_argument);
    delete chromosome;
  }
  
  TEST(ValuesTest, CrossoverDisplacedFromStartTest){
    Chromosomes::Chromosome* chromosome = new Chromosomes::Chromosome(100);

    std::vector<Genes::Gene*> *genes1 = new std::vector<Genes::Gene*>;
    for(unsigned int i = 0; i < 4; i++){
      Genes::Gene* gene = new Genes::Gene;
      gene->set_gene_value(1);
      genes1->push_back(gene);
    }  
    chromosome->set_genes(genes1);
    
  
    std::vector<Genes::Gene*> *genes2 = new std::vector<Genes::Gene*>;
    for(unsigned int i = 0; i < 3; i++){
      Genes::Gene* gene = new Genes::Gene;
      gene->set_gene_value(0);
      genes2->push_back(gene);
    }

    chromosome->crossover(1, 3, genes2);

    ASSERT_EQ(chromosome->get_genes()->at(0)->get_gene_value(), 1);
    ASSERT_EQ(chromosome->get_genes()->at(1)->get_gene_value(), 0);
    ASSERT_EQ(chromosome->get_genes()->at(2)->get_gene_value(), 0);
    ASSERT_EQ(chromosome->get_genes()->at(3)->get_gene_value(), 0);
    
    delete chromosome;
  }

  TEST(ValuesTest, CrossoverDisplacedFromEndTest){
    Chromosomes::Chromosome* chromosome = new Chromosomes::Chromosome(100);

    std::vector<Genes::Gene*> *genes1 = new std::vector<Genes::Gene*>;
    for(unsigned int i = 0; i < 4; i++){
      Genes::Gene* gene = new Genes::Gene;
      gene->set_gene_value(1);
      genes1->push_back(gene);
    }  
    chromosome->set_genes(genes1);
    
  
    std::vector<Genes::Gene*> *genes2 = new std::vector<Genes::Gene*>;
    for(unsigned int i = 0; i < 3; i++){
      Genes::Gene* gene = new Genes::Gene;
      gene->set_gene_value(0);
      genes2->push_back(gene);
    }

    chromosome->crossover(0, 2, genes2);

    ASSERT_EQ(chromosome->get_genes()->at(0)->get_gene_value(), 0);
    ASSERT_EQ(chromosome->get_genes()->at(1)->get_gene_value(), 0);
    ASSERT_EQ(chromosome->get_genes()->at(2)->get_gene_value(), 0);
    ASSERT_EQ(chromosome->get_genes()->at(3)->get_gene_value(), 1);
    
    delete chromosome;
  }  
  
  TEST(ValuesTest, CrossoverInTheMiddleTest){
    Chromosomes::Chromosome* chromosome = new Chromosomes::Chromosome(100);

    std::vector<Genes::Gene*> *genes1 = new std::vector<Genes::Gene*>;
    for(unsigned int i = 0; i < 4; i++){
      Genes::Gene* gene = new Genes::Gene;
      gene->set_gene_value(1);
      genes1->push_back(gene);
    }  
    chromosome->set_genes(genes1);
    
  
    std::vector<Genes::Gene*> *genes2 = new std::vector<Genes::Gene*>;
    for(unsigned int i = 0; i < 2; i++){
      Genes::Gene* gene = new Genes::Gene;
      gene->set_gene_value(0);
      genes2->push_back(gene);
    }

    chromosome->crossover(1,2, genes2);

    ASSERT_EQ(chromosome->get_genes()->at(0)->get_gene_value(), 1);
    ASSERT_EQ(chromosome->get_genes()->at(1)->get_gene_value(), 0);
    ASSERT_EQ(chromosome->get_genes()->at(2)->get_gene_value(), 0);
    ASSERT_EQ(chromosome->get_genes()->at(3)->get_gene_value(), 1);
    
    delete chromosome;
  }

  
  TEST(ValuesTest, CrossoverWithTheWholeChromosomeTest){
    Chromosomes::Chromosome* chromosome = new Chromosomes::Chromosome(100);

    std::vector<Genes::Gene*> *genes1 = new std::vector<Genes::Gene*>;
    for(unsigned int i = 0; i < 4; i++){
      Genes::Gene* gene = new Genes::Gene;
      gene->set_gene_value(1);
      genes1->push_back(gene);
    }  
    chromosome->set_genes(genes1);
    
  
    std::vector<Genes::Gene*> *genes2 = new std::vector<Genes::Gene*>;
    for(unsigned int i = 0; i < 4; i++){
      Genes::Gene* gene = new Genes::Gene;
      gene->set_gene_value(0);
      genes2->push_back(gene);
    }

    chromosome->crossover(0,3, genes2);

    ASSERT_EQ(chromosome->get_genes()->at(0)->get_gene_value(), 0);
    ASSERT_EQ(chromosome->get_genes()->at(1)->get_gene_value(), 0);
    ASSERT_EQ(chromosome->get_genes()->at(2)->get_gene_value(), 0);
    ASSERT_EQ(chromosome->get_genes()->at(3)->get_gene_value(), 0);
    
    delete chromosome;
  }
  
  TEST(UpdateTest, UpdatePointsTest){
    Chromosomes::Chromosome *chromosome = new Chromosomes::Chromosome(1);
    chromosome->update_points(-1);
    ASSERT_EQ(chromosome->get_points(), 0);
    delete chromosome;
  }

}
