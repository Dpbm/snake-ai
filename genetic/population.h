#pragma once

#include <vector>
#include <cstdint>
#include "../game/players/ai_player.h"
#include "../game/board.h"
#include "../helpers/utils.h"
#include "../genetic/chromosome.h"

using std::vector;
using Game::Board;
using Players::AIPlayer;
using Utils::vec2;
using Players::Directions;
using Chromosomes::Chromosome;

namespace Genetic {
  typedef struct Individual{
    Board *board;
    AIPlayer *player;
    int64_t fitness;
    uint8_t same_dir_counter;
    Directions las_dir;
    uint16_t index;
  } Individual;

  class Population{
    public:
      Population(uint16_t total, uint8_t board_w, uint8_t board_h, uint8_t total_food);
      Individual* get_best_alive_individual();
      Individual* get_best_individual();
      void next_gen();
      void run();
      uint32_t get_gen();
      Chromosome* generate_offspring(Chromosome* ch1, Chromosome* ch2);
      uint16_t get_total_alive();
      uint8_t get_total_win();
      uint16_t get_best_score();
      int64_t get_best_fitness();
      ~Population();
      
      
      //for tests (these ones could be private)
      Individual** select_parents();
      void append_individual(Individual* ind);
      Population(uint16_t total);
      

    private:
      uint32_t gen = 1;
      uint8_t total_food = 0;
      uint16_t total_ind = 0;
      uint16_t total_alive = 0;
      uint16_t total_win = 0;
      uint8_t board_w = 0;
      uint8_t board_h = 0;

      uint16_t best_score = 0;
      int64_t best_fitness = -1000000000000;
  
      void update_best_fitness(Individual* ind);

      vector<Individual*> individuals;
      vector<vec2> food_positions; 
      
      void generate_food_positions(uint8_t total, uint8_t w, uint8_t h);
      void update_individual_food_position(Individual *ind);
      void clear();
  };
};
