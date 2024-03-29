#pragma once

#include <cstdint>
#include "../../genetic/chromosome.h"
#include "../../matrix/matrix.h"
#include "../../machine/machine.h"
#include "../../machine/layer.h"
#include "player.h"
#include "../food.h"

using Chromosomes::Chromosome;
using Matrices::Matrix;
using Machine::NN;
using Machine::Layer;
using Foods::Food;

namespace Players{
  enum Directions{UP=0, DOWN=1, LEFT=2, RIGHT=3};
  
  class AIPlayer : public Player {
    public:
      AIPlayer();
      ~AIPlayer();
      Chromosome* get_chromosome();
      Matrix* get_genes_matrix(unsigned int w, unsigned int h);
      void update_input_data();
      Directions get_new_direction();
      void setup_agent(uint8_t score_step, uint16_t max_score); 
      void randomize_direction();
      bool is_trying_invalid_direction(Directions dir);
      void update_direction(Directions dir);
      Food* get_food();
      Directions get_direction();
      Directions get_last_player_dir();
      void update_last_player_dir(Directions dir);
      void save_weights(string filename);

    private:
      Chromosome* chromosome = nullptr;
      Directions direction = UP;   
      Directions last_direction = UP;

      NN* nn = new NN;   
      Layer* input_layer = new Layer(3, true);
      Matrix* input_data = new Matrix(3, 1);
  
      Food food;
  };
};
