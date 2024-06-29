#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdexcept>
#include "../genetic/population.h"
#include "../game/players/player.h"
#include "../game/board.h"
#include "../game/players/ai_player.h"
#include "../genetic/chromosome.h"
#include "../genetic/gene.h"
#include "../helpers/constants.h"
#include "../helpers/exceptions.h"

using ::testing::AllOf;
using ::testing::Ge;
using ::testing::Le;
using std::invalid_argument;
using Genetic::Population;
using Genetic::Individual;
using Players::Directions;
using Players::AIPlayer;
using Genetic::Chromosome;
using Genetic::Gene;
using Utils::InvalidValues;
using Utils::vec2;
using Game::Board;

namespace {
  TEST(CreationTest, CreateByTotalTest){
    Population p(2);

    ASSERT_EQ(p.get_total_alive(), 2);
    ASSERT_EQ(p.get_gen(), 1);
    ASSERT_EQ(p.get_total_win(), 0);
    ASSERT_EQ(p.get_best_score(), 0);
    ASSERT_EQ(p.get_total_ind(), 2);
    ASSERT_EQ(p.get_total_food(), 0);
    ASSERT_EQ(p.get_foods().size(), 0);
    ASSERT_EQ(p.get_best_fitness(), DEFAULT_BEST_FITNESS);
    ASSERT_EQ(p.get_individuals().size(), 0);
  }
  
  TEST(CreationTest, CreateCompleteModelTest){
    Population p{2, 10, 10, 2};

    vector<Individual*> individuals = p.get_individuals();

    ASSERT_EQ(p.get_total_alive(), 2);
    ASSERT_EQ(p.get_gen(), 1);
    ASSERT_EQ(p.get_total_win(), 0);
    ASSERT_EQ(p.get_best_score(), 0);
    ASSERT_EQ(p.get_total_ind(), 2);
    ASSERT_EQ(p.get_total_food(), 2);
    ASSERT_EQ(p.get_foods().size(), 2);
    ASSERT_EQ(p.get_best_fitness(), DEFAULT_BEST_FITNESS);
    ASSERT_EQ(individuals.size(), 2);

    for(size_t i = 0; i < 2; i ++){
      Individual* ind = individuals.at(i);
      ASSERT_EQ(ind->index, i);
      ASSERT_EQ(ind->fitness, 0);
      ASSERT_EQ(ind->same_dir_counter, 0);
      ASSERT_EQ(ind->last_dir, ind->player->get_dir());
    }

  }

  TEST(ValueTest, OnlyTwoIndividualsSelectParentsTest){
    Population p(2);
    Individual* ind1 = new Individual{nullptr, nullptr, 0, 0, Directions::LEFT, 0};
    Individual* ind2 = new Individual{nullptr, nullptr, 0, 0, Directions::LEFT, 0};

    p.append_individual(ind1);
    p.append_individual(ind2);

    Individual** parents = p.select_parents();
    ASSERT_EQ(parents[0], ind1);
    ASSERT_EQ(parents[1], ind2);
    delete[] parents;
  }
  
  TEST(ValueTest, ThreeIndividualsSelectParentsTest){
    Population p(3);
    Individual* ind1 = new Individual{nullptr, nullptr, 0, 0, Directions::LEFT, 0};
    Individual* ind2 = new Individual{nullptr, nullptr, 0, 0, Directions::LEFT, 0};
    Individual* ind3 = new Individual{nullptr, nullptr, 100, 0, Directions::LEFT, 0};

    p.append_individual(ind1);
    p.append_individual(ind2);
    p.append_individual(ind3);

    Individual** parents = p.select_parents();
    ASSERT_EQ(parents[0], ind3);
    ASSERT_EQ(parents[1], ind1);
    delete[] parents;
  }
  
  TEST(ValueTest, ThreeIndividualsMultipleFitValuesAscOrderSelectParentsTest){
    Population p(3);
    Individual* ind1 = new Individual{nullptr, nullptr, 40, 0, Directions::LEFT, 0};
    Individual* ind2 = new Individual{nullptr, nullptr, 9000, 0, Directions::LEFT, 0};
    Individual* ind3 = new Individual{nullptr, nullptr, 100, 0, Directions::LEFT, 0};

    p.append_individual(ind1);
    p.append_individual(ind2);
    p.append_individual(ind3);

    Individual** parents = p.select_parents();
    ASSERT_EQ(parents[0], ind2);
    ASSERT_EQ(parents[1], ind3);
    delete[] parents;
  }
  
  TEST(ValueTest, ThreeIndividualsMultipleFitValuesDescOrderSelectParentsTest){
    Population p(3);
    Individual* ind1 = new Individual{nullptr, nullptr, 40, 0, Directions::LEFT, 0};
    Individual* ind2 = new Individual{nullptr, nullptr, 100, 0, Directions::LEFT, 0};
    Individual* ind3 = new Individual{nullptr, nullptr, 9000, 0, Directions::LEFT, 0};

    p.append_individual(ind1);
    p.append_individual(ind2);
    p.append_individual(ind3);

    Individual** parents = p.select_parents();
    ASSERT_EQ(parents[0], ind3);
    ASSERT_EQ(parents[1], ind2);
    delete[] parents;
  }

  TEST(ValueTest, SixIndividualsMultipleFitValuesSelectParentsTest){
    Population p(6);
    Individual* ind1 = new Individual{nullptr, nullptr, 40, 0, Directions::LEFT, 0};
    Individual* ind2 = new Individual{nullptr, nullptr, 1000, 0, Directions::LEFT, 0};
    Individual* ind3 = new Individual{nullptr, nullptr, 200, 0, Directions::LEFT, 0};
    Individual* ind4 = new Individual{nullptr, nullptr, 3037, 0, Directions::LEFT, 0};
    Individual* ind5 = new Individual{nullptr, nullptr, 912, 0, Directions::LEFT, 0};
    Individual* ind6 = new Individual{nullptr, nullptr, 0, 0, Directions::LEFT, 0};

    p.append_individual(ind1);
    p.append_individual(ind2);
    p.append_individual(ind3);
    p.append_individual(ind4);
    p.append_individual(ind5);
    p.append_individual(ind6);

    Individual** parents = p.select_parents();
    ASSERT_EQ(parents[0], ind4);
    ASSERT_EQ(parents[1], ind2);
    delete[] parents;
  }


  TEST(ValuesTest, GenerateOffSpringChromosomesWithDifferentSizesTest){
    Population p(0);
    Chromosome ch1(10);
    Chromosome ch2(3);
    ASSERT_THROW({ p.generate_offspring(&ch1, &ch2); }, invalid_argument);
  }
  
  TEST(ValuesTest, GenerateOffSpringChromosomesWithSameSizesTest){
    Population p(0);
    Chromosome ch1(10);
    Chromosome ch2(10);
    ASSERT_NO_THROW({ p.generate_offspring(&ch1, &ch2); });
  }

  TEST(ValuesTest, GetBestIndividualTest){
    Population p(3);
    
    Individual* ind1 = new Individual{nullptr, nullptr, 40, 0, Directions::LEFT, 0};
    Individual* ind2 = new Individual{nullptr, nullptr, 1000, 0, Directions::LEFT, 0};
    Individual* ind3 = new Individual{nullptr, nullptr, 200, 0, Directions::LEFT, 0};

    p.append_individual(ind1);
    p.append_individual(ind2);
    p.append_individual(ind3);

    ASSERT_EQ(p.get_best_individual(), ind2);
    
  }
  
  TEST(ValuesTest, GetBestIndividualWithSameValuesTest){
    Population p(3);
    
    Individual* ind1 = new Individual{nullptr, nullptr, 1000, 0, Directions::LEFT, 0};
    Individual* ind2 = new Individual{nullptr, nullptr, 1000, 0, Directions::LEFT, 0};
    Individual* ind3 = new Individual{nullptr, nullptr, 1000, 0, Directions::LEFT, 0};

    p.append_individual(ind1);
    p.append_individual(ind2);
    p.append_individual(ind3);

    ASSERT_EQ(p.get_best_individual(), ind1);
    
  }
  
  TEST(ValuesTest, GetBestIndividualWithNegativeValuesTest){
    Population p(3);
    
    Individual* ind1 = new Individual{nullptr, nullptr, -1000, 0, Directions::LEFT, 0};
    Individual* ind2 = new Individual{nullptr, nullptr, -3, 0, Directions::LEFT, 0};
    Individual* ind3 = new Individual{nullptr, nullptr, -100, 0, Directions::LEFT, 0};

    p.append_individual(ind1);
    p.append_individual(ind2);
    p.append_individual(ind3);

    ASSERT_EQ(p.get_best_individual(), ind2);
    
  }
  
  TEST(ValuesTest, GetBestIndividualWithMixedValuesTest){
    Population p(3);
    
    Individual* ind1 = new Individual{nullptr, nullptr, -1000, 0, Directions::LEFT, 0};
    Individual* ind2 = new Individual{nullptr, nullptr, 0, 0, Directions::LEFT, 0};
    Individual* ind3 = new Individual{nullptr, nullptr, 10, 0, Directions::LEFT, 0};

    p.append_individual(ind1);
    p.append_individual(ind2);
    p.append_individual(ind3);

    ASSERT_EQ(p.get_best_individual(), ind3);
  }
  
  TEST(ValuesTest, GetBestIndividualNoIndividualsTest){
    Population p(3);

    ASSERT_THROW({ p.get_best_individual(); }, InvalidValues);
  }
  
  TEST(ValuesTest, GetBestIndividualAliveAllPlayersAreAliveTest){
    Population p(3);
   
    AIPlayer* player1 = new AIPlayer{10, 10}; 
    AIPlayer* player2 = new AIPlayer{10, 10}; 
    AIPlayer* player3 = new AIPlayer{10, 10}; 

    Individual* ind1 = new Individual{nullptr, player1, 1000, 0, Directions::LEFT, 0};
    Individual* ind2 = new Individual{nullptr, player2, 0, 0, Directions::LEFT, 0};
    Individual* ind3 = new Individual{nullptr, player3, 10, 0, Directions::LEFT, 0};

    p.append_individual(ind1);
    p.append_individual(ind2);
    p.append_individual(ind3);
    
    ASSERT_EQ(p.get_best_alive_individual(), ind1);
  }
  
  TEST(ValuesTest, GetBestIndividualAliveTest){
    Population p(3);
   
    AIPlayer* player1 = new AIPlayer{10, 10}; 
    AIPlayer* player2 = new AIPlayer{10, 10}; 
    AIPlayer* player3 = new AIPlayer{10, 10}; 

    Individual* ind1 = new Individual{nullptr, player1, 1000, 0, Directions::LEFT, 0};
    Individual* ind2 = new Individual{nullptr, player2, 0, 0, Directions::LEFT, 0};
    Individual* ind3 = new Individual{nullptr, player3, 10, 0, Directions::LEFT, 0};

    p.append_individual(ind1);
    p.append_individual(ind2);
    p.append_individual(ind3);

    player1->set_died();
    
    ASSERT_EQ(p.get_best_alive_individual(), ind3);
  }
  
  TEST(ValuesTest, GetBestIndividualAliveNoIndividualsAliveTest){
    Population p(3);
   
    AIPlayer* player1 = new AIPlayer{10, 10}; 
    AIPlayer* player2 = new AIPlayer{10, 10}; 
    AIPlayer* player3 = new AIPlayer{10, 10}; 

    Individual* ind1 = new Individual{nullptr, player1, 1000, 0, Directions::LEFT, 0};
    Individual* ind2 = new Individual{nullptr, player2, 0, 0, Directions::LEFT, 0};
    Individual* ind3 = new Individual{nullptr, player3, 10, 0, Directions::LEFT, 0};

    p.append_individual(ind1);
    p.append_individual(ind2);
    p.append_individual(ind3);

    player1->set_died();
    player2->set_died();
    player3->set_died();
    
    ASSERT_EQ(p.get_best_alive_individual(), ind1);
  }
  
  TEST(ValuesTest, GetBestIndividualAliveNoIndividualsTest){
    Population p(3);

    ASSERT_THROW({ p.get_best_alive_individual(); }, InvalidValues);
  }

  TEST(ValuesTest, GetFoodsTest){
    Population p{2, 10, 10, 5};
    for(vec2 food : p.get_foods()){
      ASSERT_THAT(food.x, AllOf(Ge(0), Le(9))); 
      ASSERT_THAT(food.y, AllOf(Ge(0), Le(9))); 
    }
  }

  TEST(ValuesTest, GetIndividualsTest){
    Population p(3);
   
    AIPlayer* player1 = new AIPlayer{10, 10}; 
    AIPlayer* player2 = new AIPlayer{10, 10}; 
    AIPlayer* player3 = new AIPlayer{10, 10}; 

    Board* board1 = new Board{10, 10};
    Board* board2 = new Board{10, 10};
    Board* board3 = new Board{10, 10};

    Individual* ind1 = new Individual{board1, player1, 1000, 100, Directions::LEFT, 3};
    Individual* ind2 = new Individual{board2, player2, 0, 10, Directions::RIGHT, 5};
    Individual* ind3 = new Individual{board3, player3, 10, 5, Directions::UP, 10};

    p.append_individual(ind1);
    p.append_individual(ind2);
    p.append_individual(ind3);

    vector<Individual*> inds = p.get_individuals();

    ASSERT_EQ(inds.at(0)->board, board1);
    ASSERT_EQ(inds.at(0)->player, player1);
    ASSERT_EQ(inds.at(0)->fitness, 1000);
    ASSERT_EQ(inds.at(0)->same_dir_counter, 100);
    ASSERT_EQ(inds.at(0)->last_dir, Directions::LEFT);
    ASSERT_EQ(inds.at(0)->index, 3);

    ASSERT_EQ(inds.at(1)->board, board2);
    ASSERT_EQ(inds.at(1)->player, player2);
    ASSERT_EQ(inds.at(1)->fitness, 0);
    ASSERT_EQ(inds.at(1)->same_dir_counter, 10);
    ASSERT_EQ(inds.at(1)->last_dir, Directions::RIGHT);
    ASSERT_EQ(inds.at(1)->index, 5);
    
    ASSERT_EQ(inds.at(2)->board, board3);
    ASSERT_EQ(inds.at(2)->player, player3);
    ASSERT_EQ(inds.at(2)->fitness, 10);
    ASSERT_EQ(inds.at(2)->same_dir_counter, 5);
    ASSERT_EQ(inds.at(2)->last_dir, Directions::UP);
    ASSERT_EQ(inds.at(2)->index, 10);
  }
 
  TEST(UpdateTest, UpdateBestFitnessTest){
    Population p(0);
    Individual* ind = new Individual{nullptr, nullptr, -1000, 0, Directions::LEFT, 0};
    p.update_best_fitness(ind->fitness);
    ASSERT_EQ(p.get_best_fitness(), ind->fitness);
    delete ind;
  }

  TEST(UpdaTest, UpdateBestFitnessNoChangesTest){
    Population p(0);
    Individual* ind1 = new Individual{nullptr, nullptr, -1000, 0, Directions::LEFT, 0};
    Individual* ind2 = new Individual{nullptr, nullptr, -10000, 0, Directions::LEFT, 0};
    p.update_best_fitness(ind1->fitness);
    p.update_best_fitness(ind2->fitness);
    ASSERT_EQ(p.get_best_fitness(), ind1->fitness);
    delete ind1;
    delete ind2;
  }

  TEST(ValuesTest, GetBestFitnessNoUpdatesTest){
    Population p(0);  
    ASSERT_EQ(p.get_best_fitness(), DEFAULT_BEST_FITNESS);
  }

  TEST(ValuesTest, RunTest){
    Population p(3, 10, 10, 3);
   
    for(Individual* ind : p.get_individuals()){
      ind->player->set_dir(Directions::RIGHT);
      ind->player->set_pos(4, 4);
    }

    for(size_t i = 0; i < 3; i++){
      p.run(); 
    } 

    ASSERT_EQ(p.get_total_alive(), 3);
    ASSERT_THAT(p.get_total_win(), AllOf(Ge(0), Le(3)));
    ASSERT_THAT(p.get_best_score(), AllOf(Ge(0), Le(3)));

  }
  
  TEST(ValuesTest, RunChangeTotalAliveTest){
    Population p(3, 10, 10, 3);
   
    for(Individual* ind : p.get_individuals()){
      ind->player->set_dir(Directions::RIGHT);
      ind->player->set_pos(4, 4);
    
      if(ind->index == 1){
        ind->player->set_died();
      }
    }

    for(size_t i = 0; i < 3; i++){
      p.run(); 
    } 

    ASSERT_EQ(p.get_total_alive(), 2);
    ASSERT_THAT(p.get_total_win(), AllOf(Ge(0), Le(3)));
    ASSERT_THAT(p.get_best_score(), AllOf(Ge(0), Le(3)));
  }
  
  TEST(ValuesTest, RunChangeTotalWinAndBestScoreTest){
    Population p(3, 10, 10, 3);
   
    for(Individual* ind : p.get_individuals()){
      ind->player->set_dir(Directions::RIGHT);
      ind->player->set_pos(4, 4);
    
      if(ind->index == 1){
        for(size_t j = 0; j<4; j++)
          ind->player->update_score();
      }
    }

    for(size_t i = 0; i < 3; i++){
      p.run(); 
    } 

    ASSERT_EQ(p.get_total_alive(), 2);
    ASSERT_THAT(p.get_total_win(), AllOf(Ge(1), Le(3)));
    ASSERT_THAT(p.get_best_score(), 4);
  }
}
