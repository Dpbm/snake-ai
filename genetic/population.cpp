#include <cstddef>
#include <cstdint>
#include "population.h"
#include "../machine/activation.h"
#include "../game/player.h"
#include "../game/ai_player.h"

using Players::AIPlayer;
using Players::Player;

namespace Populations{

  Population::Population(uint8_t total){
    this->individuals = new AIPlayer[total];
    this->total_individuals = total;
    this->actual_individual = &this->individuals[0];
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

  // void Population::get_new_direction(Player* player){
  //   Matrix* result = this->nn->get_output_layer()->get_values();
  //   // std::cout << "\n\n"; 
  //   // this->nn->get_layer(0)->get_values()->show();
  //   // this->nn->get_layer(1)->get_values()->show();
  //   // result->show();
  //   // std::cout << "\n\n";
  //   result->show();
  //   double biggest = 0;
  //   size_t direction = 0;
  //   for(size_t i = 0; i < 4; i++){
  //     double actual_value = result->get_position_value(0, i);
  //     if(actual_value > biggest){
  //       biggest = actual_value;
  //       direction = i;
  //     }
  //   }
  //   switch (direction) {
  //     case 0:
  //       player->direction_up();
  //       break;
  //     
  //     case 1:
  //       player->direction_down();
  //       break;

  //     case 2:
  //       player->direction_left();
  //       break;

  //     default:
  //       player->direction_right();
  //       break;
  //   }
  // }

  // void Population::update_player_direction(Player* player){
  //   this->nn->feedforward();
  //   this->get_new_direction(player);
  // }

  Population::~Population(){
    delete[] this->individuals;
  }

};
