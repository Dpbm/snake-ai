#include <cstdint>
#include "population.h"
#include "../game/ai_player.h"

using Players::AIPlayer;

namespace Populations{
  Population::Population(uint8_t total, uint8_t score_step, uint16_t max_score){
    this->individuals = new AIPlayer[total];
    this->total_individuals = total;
    this->actual_individual = &this->individuals[0];

    for(size_t i = 0; i < total; i++)
      this->individuals[i].setup_agent(score_step, max_score);
  }

  bool Population::is_the_last_individual(){
    return this->actual_individual == &this->individuals[this->total_individuals-1];
  }

  void Population::reset_individual(){
    this->actual_individual = &this->individuals[0];
  }

  void Population::update_actual_individual(){
    this->indvidual_i += 1;
    this->actual_individual = &this->individuals[this->indvidual_i];
  }

  AIPlayer* Population::get_actual_individual(){
    return this->actual_individual;
  }

  Population::~Population(){
    delete[] this->individuals;
  }

};
