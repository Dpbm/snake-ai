#include <cstdint>
#include <stdexcept>
#include <unistd.h>
#include "population.h"
#include "../game/board.h"
#include "../helpers/utils.h"
#include "chromosome.h"
#include "gene.h"

using std::invalid_argument;
using Game::Board;
using Chromosomes::Chromosome;
using Genes::Gene;
using Utils::random_int;

namespace Genetic{
  //for tests
  Population::Population(uint16_t total){
    this->total_ind = total;
  }

  Population::Population(uint16_t total, uint8_t board_w, uint8_t board_h, uint8_t total_food){
    this->total_ind = total;
    this->total_food = total_food;
    this->generate_food_positions(total_food, board_w, board_h);
  
    vec2 first_food_pos = this->food_positions.at(0);

    for(size_t i = 0; i < total; i++){
      Individual* ind = new Individual;
      ind->board = new Board(board_w, board_h);
      ind->player = new AIPlayer(board_w, board_h);

      ind->board->set_food_pos(first_food_pos.x, first_food_pos.y); 
      ind->board->add_player(ind->player);
      ind->fitness = 0;
      ind->same_dir_counter = 0;
      ind->index = i;
      ind->las_dir = ind->player->get_dir();

      this->individuals.push_back(ind); 
    }
  }

  void Population::generate_food_positions(uint8_t total, uint8_t w, uint8_t h){
    for(size_t _ = 0; _ < total; _++)
      this->food_positions.push_back(vec2{(int16_t)random_int(0, h-1), (int16_t)random_int(0, w-1)});
      // TODO: refactor this random position to a especialist class or something like this
  }

  Individual* Population::get_best_individual(){
    Individual* best_ind = this->individuals.at(0);
    int64_t best_fit = best_ind->fitness;
    for(Individual* ind: this->individuals){
      if(ind->fitness > best_fit){
        best_fit = ind->fitness;
        best_ind = ind;  
      }
    }
  
    return best_ind;
  }
  
  Individual* Population::get_best_alive_individual(){
    Individual* best_ind = nullptr;
    int64_t best_fit = 0;

    for(Individual* ind: this->individuals){
      if(ind->player->is_dead())
        continue;

      if(best_ind == nullptr){
        best_ind = ind;
        best_fit = ind->fitness;
        continue;
      }

      if(ind->fitness > best_fit){
        best_fit = ind->fitness;
        best_ind = ind;  
      }
    }
 
    if(best_ind == nullptr)
      best_ind = this->get_best_individual();

    return best_ind;
  }

  void Population::update_individual_food_position(Individual *ind){
    vec2 new_food_pos = this->food_positions.at(ind->player->get_score());
    ind->board->set_food_pos(new_food_pos.x, new_food_pos.y);
  }

  void Population::run(){
    this->total_alive = 0;

    for(Individual* ind : this->individuals){
      AIPlayer* player = ind->player;
      Board* board = ind->board;

      if(player->is_dead())
        continue;
      
      this->total_alive++;

      player->update_input_data(board->get_food(), board->get_width(), board->get_height());
      player->compute_next_dir();
      player->update_dir();
      board->update_player_pos();

      if(player->get_dir() == ind->las_dir){
        ind->same_dir_counter++;
      }else{
        ind->same_dir_counter = 0;
        ind->las_dir = player->get_dir();
      }

      // fitness for going in the same direction a bunch of times
      if(ind->same_dir_counter >= 10)
        ind->fitness += -1;

      // fitness for catching the food
      if(board->get_caught_the_food())
        ind->fitness += 5000;
    
      if(player->get_score() >= this->total_food){
        player->set_died();
        this->total_win++;
        this->total_alive--;
        ind->fitness += 20000;
        continue;
      }

      this->update_individual_food_position(ind);
    }
    if(this->total_alive == 0)
      this->gen ++;
  }

  void Population::next_gen(){
    Individual** parents = this->select_parents();
    Chromosome* offspring = this->generate_offspring(parents[0]->player->get_chromossome(), parents[1]->player->get_chromossome());
  
    //reset individuals
    //replicate
    //mutate
    //reset foods
    //clear pointers
    delete parents;
  }

  Individual** Population::select_parents(){
    uint16_t pa = 0;
    uint16_t pb = 1;
    
    for(size_t i = 1; i < this->total_ind; i++){
      Individual* ind = this->individuals.at(i);

      int64_t first_big = this->individuals.at(pa)->fitness; 
      int64_t second_big = this->individuals.at(pb)->fitness; 

      if(ind->fitness > first_big){
        int16_t last_pa = pa;
        pa = i;
        pb = last_pa;
      }else if(ind->fitness > second_big){
        pb = i;
      }
    }
  
    Individual** parents = new Individual*[2]{
      this->individuals.at(pa),
      this->individuals.at(pb),
    };

    return parents;
  }

  Chromosome* Population::generate_offspring(Chromosome* ch1, Chromosome* ch2){
    if(ch1->get_size() != ch2->get_size())
      throw invalid_argument("Both Chromosomes must have the same size!");

    uint64_t ch_size = ch1->get_size();

    Chromosome* offspring = new Chromosome(ch_size);
    Gene* offspring_genes = new Gene[ch_size];

    Gene* ch1_genes = ch1->get_genes();
    Gene* ch2_genes = ch2->get_genes();

    uint64_t pivot = random_int(0, ch_size);
    for(size_t i = 0; i < ch_size; i++){
      if(i < pivot)
        offspring_genes[i].set_gene_value(ch1_genes[i].get_gene_value());
      else
        offspring_genes[i].set_gene_value(ch2_genes[i].get_gene_value());
    }
    offspring->copy_genes(offspring_genes);

    return offspring;
  }

  void Population::append_individual(Individual* ind){
    this->individuals.push_back(ind);
  }

  uint32_t Population::get_gen(){
    return this->gen;
  }

  uint16_t Population::get_best_score(){
    uint16_t best_score = this->individuals.at(0)->player->get_score();
    for(Individual* ind: this->individuals){
      uint16_t ind_score = ind->player->get_score();
      if(ind_score > best_score)
        best_score = ind_score;
    }
    return best_score;
  }
  
  uint16_t Population::get_total_alive(){
    return this->total_alive;
  }
  
  uint8_t Population::get_total_win(){
    return this->total_win;
  }
  
  int64_t Population::get_best_fitness(){
    return this->get_best_individual()->fitness;
  }

  Population::~Population(){
    for(Individual* ind : this->individuals){
      delete ind->board;
      delete ind->player;
      delete ind;
    }   
  }
};
