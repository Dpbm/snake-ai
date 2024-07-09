#include <gtest/gtest.h>
#include "../game/players/player.h"
#include "../game/players/ai_player.h"
#include "../genetic/chromosome.h"
#include "../machine/machine.h"
#include "../matrix/matrix.h"
#include "../genetic/gene.h"
#include "../helpers/utils.h"

using Players::Directions;
using Players::AIPlayer;
using Genetic::Chromosome;
using Genetic::Gene;
using Machine::NN;
using Matrices::Matrix;
using Utils::vec2;

namespace {

  TEST(CreationTest, CreateUsingBoardTest){
    AIPlayer p{10, 10};
    ASSERT_NE(p.get_chromossome(), nullptr);
    ASSERT_NE(p.get_nn(), nullptr); 
  }

  TEST(CreationTest, CreateUsingBoardAndChromosomeTest){
    Chromosome* ch = new Chromosome(24);
    AIPlayer p{10, 10, ch};
    ASSERT_EQ(p.get_chromossome(), ch);
    ASSERT_NE(p.get_nn(), nullptr); 
  }

  TEST(CreationTest, CreateUsingBoardAndNNTest){
    NN* nn = new NN();
    AIPlayer p{10, 10, nn};
    ASSERT_EQ(p.get_chromossome(), nullptr);
    ASSERT_EQ(p.get_nn(), nn); 
  }

  TEST(ValuesTest, LoadGenesIntoWeightsTest){
    Chromosome* ch = new Chromosome(24);
    Gene* genes = ch->get_genes();
    for(size_t i = 0; i < 24; i++)
      genes[i].set_gene_value(0);

    AIPlayer p(10, 10, ch);
    p.load_genes_into_weights();
    
    NN* nn = p.get_nn();
    Matrix* w0 = nn->get_weight(0)->get_weights();
    Matrix* w1 = nn->get_weight(1)->get_weights();

    for(size_t i = 0; i < 2; i++)
      for(size_t j = 0; j < 4; j++)
        ASSERT_EQ(w0->get_position_value(i, j), 0);
    
    for(size_t i = 0; i < 4; i++)
      for(size_t j = 0; j < 4; j++)
        ASSERT_EQ(w1->get_position_value(i, j), 0);
  }

  TEST(UpdateTest, UpdateInputDataTest){
    vec2 food{2, 2};

    AIPlayer p(10, 10);
    p.set_pos(0, 0);
    p.update_input_data(food, 4, 4);
    
    Matrix* input_layer = p.get_nn()->get_input_layer()->get_values();
    ASSERT_EQ(input_layer->get_position_value(0, 0), -0.5);
    ASSERT_EQ(input_layer->get_position_value(0, 1), -0.5);   
  }


  TEST(UpdaTest, UpdateDirTest){
    AIPlayer p(10, 10);
    p.set_dir(Directions::LEFT);
    NN* nn = p.get_nn();
    Matrix* v = nn->get_output_layer()->get_values();
    v->update_value(0, 0, 0);
    v->update_value(0, 1, 1);
    v->update_value(0, 2, 0);
    v->update_value(0, 3, 0);
    p.update_dir();
    ASSERT_EQ(p.get_dir(), (int)Directions::DOWN); 
  }
  
  TEST(UpdaTest, UpdateDirEqualValuesTest){
    AIPlayer p(10, 10);
    p.set_dir(Directions::LEFT);
    NN* nn = p.get_nn();
    Matrix* v = nn->get_output_layer()->get_values();
    v->update_value(0, 0, 0);
    v->update_value(0, 1, 1);
    v->update_value(0, 2, 1);
    v->update_value(0, 3, 0);
    p.update_dir();
    ASSERT_EQ(p.get_dir(), (int)Directions::DOWN); 
  }

}
