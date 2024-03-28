#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <ctime>
#include <iterator>
#include <sstream>
#include <unistd.h>
#include "population.h"
#include "gene.h"
#include "../game/players/ai_player.h"
#include "../helpers/utils.h"

using std::stringstream;
using std::max_element;
using std::distance;
using std::size_t;
using Players::AIPlayer;
using Utils::random_int;
using Utils::get_random_x;
using Utils::get_random_y;
using Genes::Gene;

namespace Populations{
  Population::Population(uint16_t total, uint8_t score_step, uint16_t max_score){
    this->individuals = new AIPlayer[total];
    this->total_individuals = total;
    this->score_step = score_step;
    this->max_score = max_score;

    for(size_t i = 0; i < total; i++){
      this->individuals[i].setup_agent(score_step, max_score);
      this->fitness.push_back(0);
      this->same_mov_count.push_back(0);
      this->food_positions.push_back(vec2{get_random_x(FOOD_W), get_random_y(FOOD_H)});
      this->individuals[i].get_food()->set_position(this->food_positions[0].x, this->food_positions[0].y);
    }
  }

  uint32_t Population::get_generation(){
    return this->generation;
  }

  AIPlayer* Population::get_individuals(){
    return this->individuals;
  }

  AIPlayer* Population::get_player(size_t i){
    return &this->individuals[i];
  }

  uint16_t Population::get_best_score(){
    uint16_t best = 0;
    for(size_t i = 0; i < this->total_individuals; i++){
      uint16_t score = this->individuals[i].get_score();
      if(score > best)
        best = score;
    }
    return best;
  }

  bool Population::run_population(){
    uint16_t total_invalid = 0;
    bool caught_the_food = false;

    for(size_t i = 0; i < this->total_individuals; i++){
      AIPlayer* individual = &this->individuals[i];
      if(individual->is_dead()){
        total_invalid++;
        continue;
      } 

      Food* food = individual->get_food();
      int16_t fx = food->get_x();
      int16_t fy = food->get_y();
      int16_t px = individual->get_x();
      int16_t py = individual->get_y();

        
      // this->fitness.at(i) += 100;

      individual->update_input_data();
      
      Directions dir = individual->get_new_direction();
  
      if(dir == individual->get_last_player_dir())
        this->same_mov_count.at(i)++;
      else{
        this->same_mov_count.at(i)=0;
        individual->update_last_player_dir(dir);
      }   

      if(this->same_mov_count.at(i) >= 40)
        this->fitness.at(i) -= 1;

      // if(distance <= 10)
      //   this->fitness.at(i) += 6000;

      // if( fx > px && fy < py  && (dir == UP || dir == RIGHT)) // top right corner
      //   this->fitness.at(i) += 20;
      // else if( fx < px && fy < py && (dir == UP || dir == LEFT))
      //   this->fitness.at(i) += 20;
      // else if( fx < px && fy > py && (dir == DOWN || dir == LEFT))
      //   this->fitness.at(i) += 20;
      // else if( fx > px && fy > py && (dir == DOWN || dir == RIGHT))
      //   this->fitness.at(i) += 20;
      // else if(px == fx && fy < py && dir == UP)
      //   this->fitness.at(i) += 100;
      // else if(px == fx && fy > py && dir == DOWN)
      //   this->fitness.at(i) += 100;
      // else if(py == fy && fx < px && dir == LEFT)
      //   this->fitness.at(i) += 100;
      // else if(py == fy && fx > px && dir == RIGHT)
      //   this->fitness.at(i) += 100;
        

      // if((dir == LEFT && fx > px) || (dir == RIGHT && fx < px))
      //   this->fitness.at(i) -= 1000;
      // if((dir == UP && fy > py) || (dir == DOWN && fy < py))
      //   this->fitness.at(i) -= 1000;


      // if(individual->is_trying_invalid_direction(dir))
      //   this->fitness.at(i) -= 100;

      // if(dir != individual->get_direction())
      //   this->fitness.at(i) += 200;

      // if(px == fx || py == fy)
      //   this->fitness.at(i) += 10;

      // if((WIDTH - px <= 10 || px <= 10) && (dir == UP || dir == DOWN))
      //   this->fitness.at(i) += 100;
      // 
      // if((HEIGHT - py <= 10 || py <= 10) && (dir == LEFT || dir == RIGHT))
      //   this->fitness.at(i) += 100;

      individual->update_direction(dir); 
      individual->update_position();

      if(individual->is_dead()){
        total_invalid++;
        this->fitness.at(i)--;
        continue;
      }

      if(individual->collision(fx, fy)){
        individual->update_score();
        this->fitness.at(i) += 10000;
        caught_the_food = true;
      }
    }

    bool finished_gen = total_invalid == this->total_individuals;

    return finished_gen || caught_the_food;
  }

  void Population::update_gen(){
    this->generation ++;
  }

  void Population::next_generation(){
    // for(size_t i = 0; i < this->total_individuals; i++)
    //   std::cout << this->fitness.at(i) << " ";
    // std::cout << std::endl;
  
    uint16_t max_fitness_i = this->get_best_fitness_i();
    this->fitness.at(max_fitness_i) = this->fitness[max_fitness_i]-10000;
    uint16_t max_fitness_2_i = this->get_best_fitness_i();

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
      individual->mutate(0.1); 
      // individual->show();
    }

    this->food_i++;

    delete[] offspring_genes;
  }  
  
  void Population::reset_individuals(){
    delete[] this->individuals;
    this->fitness.clear();
    this->same_mov_count.clear();

    this->individuals = new AIPlayer[this->total_individuals];
  
    for(size_t i = 0; i < this->total_individuals; i++){
      this->individuals[i].setup_agent(this->score_step, this->max_score);
      this->fitness.push_back(0);
      this->same_mov_count.push_back(0);
    }
  }

  uint16_t Population::get_best_fitness_i(){
    vector<int64_t>::iterator max_fitness = max_element(this->fitness.begin(), this->fitness.end()); 
    uint16_t max_fitness_i = distance(this->fitness.begin(), max_fitness);
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
    if(!best_player->is_dead())
      return best_player;
    
    int64_t max_fitness = -100000000;
    uint16_t best_i = 0;
    for(size_t i = 0; i < this->total_individuals; i ++){
      int64_t fitness = this->fitness[i];
      if(fitness > max_fitness && !this->individuals[i].is_dead()){
        max_fitness = fitness;
        best_i = i;
      }
    }
    
    return &this->individuals[best_i];
  }

  void Population::save_weights(){
    stringstream string;
    string << time(0) << "-weights.wg";
    this->get_best_player()->save_weights(string.str());
  }

  Population::~Population(){
    delete[] this->individuals;
  }
};
