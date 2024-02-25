#include <gtest/gtest.h>
#include "../genetic/population.h"
#include "../genetic/chromosome.h"

using Populations::Population;
using Chromosomes::Chromosome;

namespace {
  TEST(CreationTest, CreateIndividualsSetTest){
    Population *population = new Population(5, 10, 100);
    ASSERT_EQ(population->get_total_individuals(), 5);
    ASSERT_EQ(population->get_individuals()[0].get_size(), 10);
    ASSERT_EQ(population->get_chromosomes_size(), 10);
    delete population;
  }

  TEST(CreationTest, CreatePopulationFromChromosomesTest){
    Chromosome* chromosomes = new Chromosome[2];
    chromosomes[0].add_genes(3, 100);
    chromosomes[1].add_genes(3, 100);
    
    Population *population = new Population(chromosomes, 2, 100);
    ASSERT_EQ(population->get_total_individuals(), 2);
    ASSERT_EQ(population->get_chromosomes_size(), 3);
    delete population;
  }

  
  TEST(UpdateTest, RewardAllTest){
    Population *population = new Population(2, 5, 100);

    int* rewards = new int[2];
    rewards[0] = 100;
    rewards[1] = 100;
    population->reward_all(rewards);
    
    ASSERT_EQ(population->get_individuals()[0].get_points(), 200);
    ASSERT_EQ(population->get_individuals()[1].get_points(), 200);

    delete population;
    delete[] rewards;
  }  
  

  TEST(UpdateTest, NewGenerationTest){
    Chromosome *chromosomes = new Chromosome[3];
    chromosomes[0].add_genes(3, 100);
    chromosomes[1].add_genes(3, 100);
    chromosomes[2].add_genes(3, 100);
    
    Population *population = new Population(chromosomes, 3,  100);
    int* rewards = new int[3]{100, -100, 200};
    population->reward_all(rewards);
    population->new_generation(200);
    
    ASSERT_EQ(population->get_individuals()[0].get_points(), 200);
    ASSERT_EQ(population->get_individuals()[1].get_points(), 100);
    ASSERT_EQ(population->get_individuals()[2].get_points(), 300);
    delete population;
    delete[] rewards;
  }

  TEST(ValuesTest, GetHighestScorePositiveScoresTest){
    Population *population = new Population(4, 10, 0);
    Chromosome* individuals = population->get_individuals();
    
    int* rewards = new int[4]{100, 200, 100, 3};
    population->reward_all(rewards);

    ASSERT_EQ(population->get_highest_score(), 200);
    delete population;
    delete[] rewards;
  }
  
  TEST(ValuesTest, GetHighestScoreNegativeScoresTest){
    Population *population = new Population(4, 10, 0);
    Chromosome* individuals = population->get_individuals();
      
    int* rewards = new int[4]{-100, -200, -100, -3};
    population->reward_all(rewards);

    ASSERT_EQ(population->get_highest_score(), -3);
    delete population;
    delete[] rewards;
  }
  
  TEST(ValuesTest, GetHighestScoreNegativeScoresWithZeroTest){
    Population *population = new Population(4, 10, 0);
    Chromosome* individuals = population->get_individuals();
   
    int* rewards = new int[4]{-100, -200, -100, 0};
    population->reward_all(rewards);

    ASSERT_EQ(population->get_highest_score(), 0);
    delete population;
    delete[] rewards;
  }
  
  TEST(ValuesTest, GetHighestScoreWithMixedScoresTest){
    Population *population = new Population(4, 10, 0);
    Chromosome* individuals = population->get_individuals();
    
    int* rewards = new int[4]{-3, 0, -100000, 10000};
    population->reward_all(rewards);

    ASSERT_EQ(population->get_highest_score(), 10000);
    delete population;
    delete[] rewards;
  }
}
