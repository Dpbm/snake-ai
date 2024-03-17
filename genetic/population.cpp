#include <iostream>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <SDL2/SDL_thread.h>
#include "population.h"
#include "../game/players/ai_player.h"

using std::cout;
using std::endl;
using std::sqrt;
using std::pow;
using std::size_t;
using Players::AIPlayer;

namespace Populations{
  Population::Population(uint8_t total, uint8_t score_step, uint16_t max_score){
    this->individuals = new AIPlayer[total];
    this->total_individuals = total;
    this->score_step = score_step;
    this->max_score = max_score;
    // this->actual_individual = &this->individuals[0];
    // this->fitness = new int64_t[total];

    for(size_t i = 0; i < total; i++)
      this->individuals[i].setup_agent(score_step, max_score);
  }

  // bool Population::is_the_last_individual(){
  //   return this->actual_individual == &this->individuals[this->total_individuals-1];
  // }

  // void Population::update_direction_data(Directions dir){
  //   if(!this->actual_individual->is_the_opposite_direction(dir))
  //     this->fitness[this->indvidual_i] -= 100;   
  // }
  // 
  // void Population::update_points_data(){
  //   this->fitness[this->indvidual_i] += 200;   
  // }

  // void Population::reset_agents(){
  //   this->distances.clear();
  //   delete[] this->fitness;
  //   delete[] this->individuals;
  //   

  //   this->fitness = new int64_t[this->total_individuals];
  //   this->individuals = new AIPlayer[this->total_individuals];
  //   for(size_t i = 0; i < this->total_individuals; i++)
  //     this->individuals[i].setup_agent(score_step, max_score);

  //   // this->indvidual_i = 0;
  //   // this->actual_individual = &this->individuals[0];
  // }

  // void Population::update_distance_data(int16_t fx, int16_t fy){
  //   // put on ai_player
  //   uint16_t d = sqrt(pow(fx-this->actual_individual->get_x(),2) + pow(fy-this->actual_individual->get_y(), 2));
  //   this->distances.push_back(d);
  // }

  // void Population::update_actual_individual(){
  //   this->indvidual_i += 1;
  //   this->actual_individual = &this->individuals[this->indvidual_i];
  // }

  // AIPlayer* Population::get_actual_individual(){
  //   return this->actual_individual;
  // }

  void Population::run_population(int16_t fx, int16_t fy){
    auto individual_run = [](uint8_t individual_i, AIPlayer* individual, int16_t fx, int16_t fy){
      individual->randomize_direction();

      cout << "======================" << endl;
      cout << "Thread for individual: " << individual_i << endl;
      cout << "food x: " << fx << endl;
      cout << "food y: " << fy << endl;
      cout << "player x: " << individual->get_x() << endl;
      cout << "player y:" << individual->get_y() << endl;
      cout << "player mov_x:" << individual->get_mov_x() << endl;
      cout << "player mov_y:" << individual->get_mov_y() << endl << endl;


      while(!individual->is_die() || individual->get_score() != 1){
        individual->update_input_data(fx, fy);
        
        Directions dir = individual->get_new_direction();
        individual->update_direction(dir); 
        individual->update_position();

        if(individual->collision(fx, fy))
          individual->update_score();
      }
    };
   
 
    typedef struct ThreadData {
      uint8_t individual_i;
      AIPlayer* individual;
      int16_t fx;
      int16_t fy;
    }ThreadData;

    for(size_t i = 0; i < this->total_individuals; i++){
      cout << i << endl;
      AIPlayer* player = &this->individuals[i];
      ThreadData* data = new ThreadData;
      data->individual_i = i;
      data->individual = player;
      data->fx = fx;
      data->fy = fy;


      SDL_CreateThread(individual_run, data);
    }  
  }

  
  Population::~Population(){
    delete[] this->individuals;
    // delete[] this->fitness;
  }
};
