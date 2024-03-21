#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <unistd.h>
#include "population.h"
#include "gene.h"
#include "../game/players/ai_player.h"
#include "../helpers/utils.h"

using std::max_element;
using std::distance;
using std::size_t;
using Players::AIPlayer;
using Utils::random_int;
using Genes::Gene;
using Players::Directions::UP;
using Players::Directions::DOWN;
using Players::Directions::LEFT;
using Players::Directions::RIGHT;

namespace Populations{
  Population::Population(uint8_t total, uint8_t score_step, uint16_t max_score){
    this->individuals = new AIPlayer[total];
    this->total_individuals = total;
    this->score_step = score_step;
    this->max_score = max_score;

    for(size_t i = 0; i < total; i++){
      this->individuals[i].setup_agent(score_step, max_score);
      this->fitness.push_back(0);
    }
  }

  uint32_t Population::get_generation(){
    return this->generation;
  }

  AIPlayer* Population::get_individuals(){
    return this->individuals;
  }

  bool Population::run_population(){
    uint8_t total_invalid = 0;

    for(size_t i = 0; i < this->total_individuals; i++){
      AIPlayer* individual = &this->individuals[i];
      Food* food = individual->get_food();
      int16_t fx = food->get_x();
      int16_t fy = food->get_y();

      if(individual->is_die()){
        total_invalid++;
        continue;
      }
        
      // this->fitness.at(i) += 100;

      individual->update_input_data();
      
      Directions dir = individual->get_new_direction();
      
      int16_t px = individual->get_x();
      int16_t py = individual->get_y();
      
      if((dir == LEFT && fx > px) || (dir == RIGHT && fx < px))
        this->fitness.at(i) -= 1000;
      if((dir == UP && fy > py) || (dir == DOWN && fy < py))
        this->fitness.at(i) -= 1000;


      // if(individual->is_trying_invalid_direction(dir))
      //   this->fitness.at(i) -= 100;

      // if(dir != individual->get_direction())
      //   this->fitness.at(i) += 200;

      individual->update_direction(dir); 
      individual->update_position();

      if(individual->collision(fx, fy)){
        individual->update_score();
        food->update_position();
        this->fitness.at(i) += 10000;
      }
    }

    bool finished_gen = total_invalid == this->total_individuals;

    return finished_gen;
  }

  void Population::update_gen(){
    this->generation ++;
  }

  void Population::next_generation(){
    uint8_t max_fitness_i = this->get_best_fitness_i();
    this->fitness.at(max_fitness_i) = this->fitness[max_fitness_i]-10000;
    uint8_t max_fitness_2_i = this->get_best_fitness_i();

    AIPlayer* best = &this->individuals[max_fitness_i];
    AIPlayer* second_best = &this->individuals[max_fitness_2_i];
    
    Chromosome* best_chromosome = best->get_chromosome();
    Chromosome* second_best_chromosome = second_best->get_chromosome();
    
    uint16_t chromosome_size = best_chromosome->get_size();
    uint16_t pivot = random_int(0, chromosome_size);

    Gene* best_genes = best_chromosome->get_genes();
    Gene* second_best_genes = second_best_chromosome->get_genes();
    Gene* offspring_genes = new Gene[chromosome_size];
    for(size_t i = 0; i < chromosome_size; i++){
      if(i <= pivot)
        offspring_genes[i].set_gene_value(best_genes[i].get_gene_value());
      else
        offspring_genes[i].set_gene_value(second_best_genes[i].get_gene_value());
    }

    this->reset_individuals();
    
   for(size_t i = 0; i < this->total_individuals; i++){
      Chromosome* individual = this->individuals[i].get_chromosome();
      individual->copy_genes(offspring_genes);
      individual->mutate(0.3);
  
      // individual->show();
    }



    delete[] offspring_genes;
  }  
  
  void Population::reset_individuals(){
    delete[] this->individuals;
    this->fitness.clear();

    this->individuals = new AIPlayer[this->total_individuals];
  
    for(size_t i = 0; i < this->total_individuals; i++){
      this->individuals[i].setup_agent(this->score_step, this->max_score);
      this->fitness.push_back(0);
    }
  }

  uint8_t Population::get_best_fitness_i(){
    vector<int64_t>::iterator max_fitness = max_element(this->fitness.begin(), this->fitness.end()); 
    uint8_t max_fitness_i = distance(this->fitness.begin(), max_fitness);
    return max_fitness_i;
  }

  int64_t Population::get_best_fitness(){
    return this->fitness.at(this->get_best_fitness_i());
  }

  AIPlayer* Population::get_best_player(){
    return &this->individuals[this->get_best_fitness_i()];
  }

  AIPlayer* Population::get_best_player_alive(){
    AIPlayer* best_player = this->get_best_player();
    if(!best_player->is_die())
      return best_player;
    
    int64_t max_fitness = -100000000;
    uint8_t best_i = 0;
    for(size_t i = 0; i < this->total_individuals; i ++){
      int64_t fitness = this->fitness[i];
      if(fitness > max_fitness && !this->individuals[i].is_die()){
        max_fitness = fitness;
        best_i = i;
      }
    }
    
    return &this->individuals[best_i];
  }
  
  Population::~Population(){
    delete[] this->individuals;
  }
};
