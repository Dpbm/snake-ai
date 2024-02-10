#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>
#include "../genetic/population.h"
#include "../genetic/chromosome.h"

using std::vector;
using Populations::Population;
using Chromosomes::Chromosome;

namespace {
  TEST(CreationTest, CreateIndividualsSetTest){
    Population *population = new Population(5, 10, 100);
    ASSERT_EQ(population->get_individuals()->size(), 5);
    ASSERT_EQ(population->get_total_individuals(), 5);
    ASSERT_EQ(population->get_individuals()->at(0)->get_size(), 10);
    ASSERT_EQ(population->get_chromosomes_size(), 10);
    delete population;
  }

  TEST(CreationTest, CreateNoIndividualsTest){
    Population *population = new Population;
    ASSERT_EQ(population->get_total_individuals(), 0);
    ASSERT_EQ(population->get_chromosomes_size(), 0);
    ASSERT_EQ(population->get_individuals()->size(), 0);
    delete population;
  }   

  TEST(UpdateTest, SetIndividualsTest){
    Population *population = new Population;
    vector<Chromosome*>* chromosomes = new vector<Chromosome*>;
    chromosomes->push_back(new Chromosome(3, 100));
    chromosomes->push_back(new Chromosome(3, 100));
    
    population->set_individuals(chromosomes);
    ASSERT_EQ(population->get_individuals()->size(), 2);
    ASSERT_EQ(population->get_total_individuals(), 2);
    ASSERT_EQ(population->get_chromosomes_size(), 3);
    delete population;
  }

  
  TEST(UpdateTest, SetIndividualsWithNoChromosomesTest){  
    Population *population = new Population;
    EXPECT_THROW({
      population->set_individuals(new vector<Chromosome*>);
    }, std::invalid_argument);
    delete population;
  }
  
  TEST(UpdateTest, RewardIndividualTest){
    Population *population = new Population;
    Chromosome* chromosome = new Chromosome(5, 100);
    vector<Chromosome*>*chromosomes = new vector<Chromosome*>;
    chromosomes->push_back(chromosome);
    population->set_individuals(chromosomes);

    population->reward_individual(chromosome, 100);
  
    ASSERT_EQ(chromosome->get_points(), 200);
    delete population;
  }

  TEST(UpdateTest, RewardAllTest){
    Population *population = new Population(2, 5, 100);

    vector<int>* rewards = new vector<int>;
    rewards->push_back(100); 
    rewards->push_back(100); 

    population->reward_all(rewards);

    for(Chromosome* chromosome: (*population->get_individuals()))
      ASSERT_EQ(chromosome->get_points(), 200);

    delete population;
  }  
  
  TEST(UpdateTest, WrongRewardSizeTest){
    Population *population = new Population(2, 5, 100);

    vector<int>* rewards = new vector<int>;
    rewards->push_back(100); 

    EXPECT_THROW({ population->reward_all(rewards); }, std::invalid_argument);   

    delete population;
  }  

  TEST(UpdateTest, NewGenerationTest){
    Population *population = new Population;
    vector<Chromosome*> *chromosomes = new vector<Chromosome*>;
      
    Chromosome* chromosome1 = new Chromosome(3, 100);
    Chromosome* chromosome2 = new Chromosome(3, 100);
    Chromosome* chromosome3 = new Chromosome(3, 100);
    chromosomes->push_back(chromosome1);    
    chromosomes->push_back(chromosome2);    
    chromosomes->push_back(chromosome3);    

    population->set_individuals(chromosomes);

    population->reward_individual(chromosome1, 100);
    population->reward_individual(chromosome2, -100);
    population->reward_individual(chromosome3, 200);

    population->new_generation(200);

    ASSERT_EQ(population->get_individuals()->at(0), chromosome1);
    ASSERT_NE(population->get_individuals()->at(1), chromosome2);
    ASSERT_EQ(population->get_individuals()->at(2), chromosome3);

    delete population;
  }

  TEST(ValuesTest, TestGetIndividuals){
    Population *population = new Population;
    vector<Chromosome*> *chromosomes = new vector<Chromosome*>;
      
    Chromosome* chromosome1 = new Chromosome(3, 100);
    Chromosome* chromosome2 = new Chromosome(3, 100);
    chromosomes->push_back(chromosome1);
    chromosomes->push_back(chromosome2);
    population->set_individuals(chromosomes);

    ASSERT_EQ(population->get_individuals()->at(0), chromosome1);
    ASSERT_EQ(population->get_individuals()->at(1), chromosome2);
    delete population; 
  }
}
