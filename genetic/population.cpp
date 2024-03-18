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
      
      if(individual->is_trying_invalid_direction(dir))
        this->fitness.at(i) -= 100;

      individual->update_direction(dir); 
      individual->update_position();

      if(individual->collision(fx, fy)){
        individual->update_score();
        this->fitness.at(i) += 200;
      }
    }
    return total_invalid == this->total_individuals;
  }

  void Population::next_generation(){
    vector<int64_t>::iterator max_fitness = max_element(this->fitness.begin(), this->fitness.end()); 
    uint8_t max_fitness_i = distance(this->fitness.begin(), max_fitness);

    this->fitness.at(max_fitness_i) = this->fitness[max_fitness_i]-10000;
    vector<int64_t>::iterator max_fitness_2 = max_element(this->fitness.begin(), this->fitness.end()); 
    uint8_t max_fitness_2_i = distance(this->fitness.begin(), max_fitness_2);

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
  
      individual->show();
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
  
  Population::~Population(){
    delete[] this->individuals;
  }
};
