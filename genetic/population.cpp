#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <unistd.h>
#include "population.h"
#include "../game/board.h"
#include "../helpers/utils.h"
#include "../helpers/exceptions.h"
#include "../helpers/constants.h"
#include "chromosome.h"
#include "gene.h"

using std::cout;
using std::endl;
using std::invalid_argument;
using Game::Board;
using Genetic::Chromosome;
using Genetic::Gene;
using Utils::random_int;
using Utils::InvalidValues;
using Players::Directions::LEFT;

namespace Genetic{
  Population::Population(uint16_t total){
    //It was created especially for tests, don't use it for any real code! 
    this->total_ind = total;
    this->total_alive = total;
  }

  Population::Population(uint16_t total, uint8_t board_w, uint8_t board_h, uint8_t total_food){
    this->total_ind = total;
    this->total_food = total_food;
    this->board_h = board_h;
    this->board_w = board_w;
    this->total_alive = total;

    this->generate_food_positions();
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
      ind->last_dir = ind->player->get_dir();

      this->individuals.push_back(ind); 
    }
  }

  void Population::generate_food_positions(){
    for(size_t _ = 0; _ < this->total_food; _++)
      this->food_positions.push_back(vec2{(int16_t)random_int(0, this->board_h-1), (int16_t)random_int(0, this->board_w-1)});
      // TODO: refactor this random position to a especialist class or something like this
  }

  Individual* Population::get_best_individual(){
    if(this->individuals.size() <= 0)
      throw InvalidValues();

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
    if(this->individuals.size() <= 0)
      throw InvalidValues();
    
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

      if(player->get_dir() == ind->last_dir){
        ind->same_dir_counter++;
      }else{
        ind->same_dir_counter = 0;
        ind->last_dir = player->get_dir();
      }

      // fitness for going in the same direction a bunch of times
      if(ind->same_dir_counter >= 10)
        ind->fitness += -1;

      // fitness for catching the food
      if(board->get_caught_the_food())
        ind->fitness += 5000;
   
      uint16_t score = player->get_score();
      if(score > this->best_score)
        this->best_score = score;

      if(score >= this->total_food){
        player->set_died();
        this->total_win++;
        this->total_alive--;
        ind->fitness += 20000;
        this->update_best_fitness(ind->fitness);
        continue;
      }

      if(player->is_dead()){
        ind->fitness += -1000;
        this->update_best_fitness(ind->fitness);
        continue;
      }

      this->update_best_fitness(ind->fitness);
      this->update_individual_food_position(ind);
    }
  }

  void Population::update_best_fitness(int64_t fit){
    if(fit > this->best_fitness)
      this->best_fitness = fit;
  }

  void Population::next_gen(){
    cout << "gen: " << this->gen << endl;  
    cout << "best fit: " << this->best_fitness << endl;  
    cout << "best score: " << this->best_score << endl; 

    cout << "saving weights..." << endl << endl;
    this->get_best_individual()->player->save_weights(this->gen);
    
    this->gen++;
    this->best_score = 0;
    this->total_alive = this->total_ind; 
    this->best_fitness = DEFAULT_BEST_FITNESS;
    
    Individual** parents = this->select_parents();
    Chromosome* offspring = this->generate_offspring(parents[0]->player->get_chromossome(), parents[1]->player->get_chromossome());
    delete parents;
    Gene* offspring_genes = offspring->get_genes();

    uint64_t offspring_ch_size = offspring->get_size();

    this->clear();
    this->individuals.clear();
    this->food_positions.clear();
    this->generate_food_positions();
    vec2 first_food_pos = this->food_positions.at(0);
    
    for(size_t i = 0; i < this->total_ind; i++){
      Individual* ind = new Individual;
      ind->board = new Board(board_w, board_h);
      
      if(i == 0)
        ind->player = new AIPlayer(board_w, board_h, offspring);
      else{
        Chromosome* player_chromosome = new Chromosome(offspring_ch_size);
        player_chromosome->copy_genes(offspring_genes);
        player_chromosome->mutate(0.3);

        ind->player = new AIPlayer(board_w, board_h, player_chromosome);
      }

      ind->board->set_food_pos(first_food_pos.x, first_food_pos.y); 
      ind->board->add_player(ind->player);
      ind->fitness = 0;
      ind->same_dir_counter = 0;
      ind->index = i;
      ind->last_dir = ind->player->get_dir();

      this->individuals.push_back(ind); 
    }
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
    return this->best_score;
  }
  
  uint16_t Population::get_total_alive(){
    return this->total_alive;
  }
  
  uint8_t Population::get_total_win(){
    return this->total_win;
  }
  
  int64_t Population::get_best_fitness(){
    return this->best_fitness;
  }

  void Population::clear(){
    for(Individual* ind : this->individuals){
      delete ind->board;
      delete ind->player;
      delete ind;
    }   
  }

  uint16_t Population::get_total_ind(){
    return this->total_ind;
  } 

  vector<vec2> Population::get_foods(){
    return  this->food_positions;    
  }

  uint8_t Population::get_total_food(){
    return this->total_food;
  }

  vector<Individual*> Population::get_individuals(){
    return this->individuals;
  }

  Population::~Population(){
    this->clear();
  }
};
