#include <cstddef>
#include <cstdint>
#include <unistd.h>
#include "population.h"
#include "../game/players/ai_player.h"

using std::size_t;
using Players::AIPlayer;

namespace Populations{
  Population::Population(uint8_t total, uint8_t score_step, uint16_t max_score){
    this->individuals = new AIPlayer[total];
    this->total_individuals = total;
    this->score_step = score_step;
    this->max_score = max_score;

    for(size_t i = 0; i < total; i++)
      this->individuals[i].setup_agent(score_step, max_score);
  }

  AIPlayer* Population::get_individuals(){
    return this->individuals;
  }

  bool Population::run_population(int16_t fx, int16_t fy){
    uint8_t total_invalid = 0;

    for(size_t i = 0; i < this->total_individuals; i++){
      AIPlayer* individual = &this->individuals[i];
      
      if(individual->is_die() || individual->get_score() > 0){
        total_invalid++;
        continue;
      }

      individual->update_input_data(fx, fy);
      
      Directions dir = individual->get_new_direction();
      individual->update_direction(dir); 
      individual->update_position();

      if(individual->collision(fx, fy)){
        individual->update_score();
      }
    }
    return total_invalid == this->total_individuals;
  }

  void Population::next_generation(){
    this->reset_individuals();
  }  
  
  void Population::reset_individuals(){
    delete[] this->individuals;
    this->individuals = new AIPlayer[this->total_individuals];

    for(size_t i = 0; i < this->total_individuals; i++)
      this->individuals[i].setup_agent(this->score_step, this->max_score);
  }
  
  Population::~Population(){
    delete[] this->individuals;
  }
};
