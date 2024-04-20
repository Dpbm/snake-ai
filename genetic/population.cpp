#include <cstdint>
#include <unistd.h>
#include "population.h"
#include "../game/board.h"
#include "../helpers/utils.h"

using Game::Board;
using Utils::random_int;

namespace Genetic{
  Population::Population(uint16_t total, uint8_t score_step, uint8_t board_w, uint8_t board_h, uint8_t total_steps){
    this->total_ind = total;
    this->generate_food_positions(total_steps, board_w, board_h);

    vec2 first_food_pos = this->food_positions.at(0);

    for(size_t i = 0; i < total; i++){
      Individual* ind = new Individual;
      ind->board = new Board(board_w, board_h);
      ind->player = new AIPlayer(score_step, board_w, board_h);

      ind->board->set_food_pos(first_food_pos.x, first_food_pos.y); 
      ind->board->add_player(ind->player);

      this->individuals.push_back(ind); 
    }
  }

  void Population::generate_food_positions(uint8_t total, uint8_t w, uint8_t h){
    for(size_t _ = 0; _ < total; _++)
      this->food_positions.push_back(vec2{random_int(0, h-1), random_int(0, w-1)});
      // TODO: refactor this random position to a especialist class or something like this
  }

  Individual* Population::get_best_individual(){
    //TODO: change that, for sure
    return this->individuals.at(0); 
  }

  Population::~Population(){
    for(Individual* ind : this->individuals){
      delete ind->board;
      delete ind->player;
      delete ind;
    }   
  }
};
