#pragma once

#include <vector>
#include <cstdint>
#include "../game/players/ai_player.h"
#include "../game/board.h"
#include "../helpers/utils.h"

using std::vector;
using Game::Board;
using Players::AIPlayer;
using Utils::vec2;

namespace Genetic {
  typedef struct Individual{
    Board *board;
    AIPlayer *player;
    uint8_t actual_food = 0;
  } Individual;

  class Population{
    public:
      Population(uint16_t total, uint8_t score_step, uint8_t board_w, uint8_t board_h, uint8_t total_steps);
      Individual* get_best_individual();
      ~Population();

    private:
      uint16_t total_ind = 0;
      vector<Individual*> individuals;
      vector<vec2> food_positions; 
      
      void generate_food_positions(uint8_t total, uint8_t w, uint8_t h);
  };
};
