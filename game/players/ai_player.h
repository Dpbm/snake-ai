#pragma once

#include <cstdint>
#include "../../genetic/chromosome.h"
#include "../../matrix/matrix.h"
#include "../../machine/machine.h"
#include "../../machine/layer.h"
#include "../../helpers/utils.h"
#include "player.h"

using Genetic::Chromosome;
using Matrices::Matrix;
using Machine::NN;
using Utils::vec2;

namespace Players{
  class AIPlayer : public Player {
    public:
      AIPlayer(uint8_t board_w, uint8_t board_h);
      AIPlayer(uint8_t board_w, uint8_t board_h, Chromosome* chromosome);
      AIPlayer(uint8_t board_w, uint8_t board_h, NN* nn);
      ~AIPlayer();
  
      void save_weights();
      void save_weights(uint32_t gen);

      void load_genes_into_weights();
      void update_input_data(const vec2& food, uint16_t w, uint16_t h);
      void compute_next_dir();
      Chromosome* get_chromossome();
      void update_dir();

    private:
      Chromosome* chromosome = nullptr;
      NN* nn = new NN;   

      void setup_nn();
      void setup_chromosome();
  };
};
