#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>
#include "../machine/machine.h"
#include "../machine/layer.h"
#include "../matrix/matrix.h"
#include "../game/players/ai_player.h"

using std::size_t;
using std::vector;
using Machine::NN;
using Machine::Layer;
using Matrices::Matrix;
using Players::AIPlayer;
using Players::Directions;

namespace Populations {
  typedef struct vec2{
    uint16_t x;
    uint16_t y;
  } vec2;

  class Population{
    public:
      Population(uint16_t total, uint8_t score_step, uint16_t max_score);
      bool run_population();
      AIPlayer* get_individuals();
      void next_generation();
      int64_t get_best_fitness();
      uint16_t get_best_fitness_i();
      AIPlayer* get_best_player();
      AIPlayer* get_best_player_alive();
      uint32_t get_generation();
      void update_gen();
      uint16_t get_best_score();
      AIPlayer* get_player(size_t i);
      ~Population();
      void save_weights();

    private:
      uint32_t generation = 1;
      uint32_t max_generation = 1000;
      uint16_t total_individuals = 0;
      AIPlayer* individuals = nullptr;

      vector<int64_t> fitness;
      vector<uint32_t> same_mov_count;
      vector<vec2> food_positions;
      uint32_t food_i = 0;

      uint8_t score_step;
      uint16_t max_score;

      void reset_individuals();
  };
};
