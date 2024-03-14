#include <cstddef>
#include <cstdint>
#include "population.h"
#include "ai_player.h"
#include "../machine/activation.h"
#include "../game/player.h"

using AIAgent::AIPlayer;
using Players::Player;

namespace Populations{

  Population::Population(uint8_t total){
    this->individuals = new AIPlayer[total];
    this->total_individuals = total;
    this->actual_individual = &this->individuals[0];
    
    this->setup_nn();

    uint16_t genes_array_size = 0;
    for(size_t weight_i = 0; weight_i < this->nn->get_total_weights(); weight_i++){
      Weights* weights = this->nn->get_weight(weight_i);
      genes_array_size += weights->get_width()*weights->get_height();
    }
    this->total_weights = genes_array_size;
    
    for(size_t i = 0; i < total; i++)
      this->individuals[i].setup_choromosome(this->total_weights);
  }

  void Population::setup_nn(){
    this->nn->add_layer(this->input_layer);
    this->nn->add_layer(4);
    this->nn->add_layer(4);
    
    this->nn->get_layer(1)->set_activation_function(Activations::tanh);
    this->nn->get_layer(2)->set_activation_function(Activations::softmax);
    this->input_layer->set_values(this->input_data);
  }

  void Population::load_genes_into_weights(){
    for(size_t weight_i = 0; weight_i < this->nn->get_total_weights(); weight_i++){
      uint8_t w = this->nn->get_weight(weight_i)->get_width();
      uint8_t h = this->nn->get_weight(weight_i)->get_height();

      this->nn->get_weight(weight_i)->load_weights(
        this->actual_individual->get_genes_matrix(w, h)
      );
    }
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

  void Population::get_new_direction(Player* player){
    Matrix* result = this->nn->get_output_layer()->get_values();
    // std::cout << "\n\n"; 
    // this->nn->get_layer(0)->get_values()->show();
    // this->nn->get_layer(1)->get_values()->show();
    // result->show();
    // std::cout << "\n\n";
    result->show();
    double biggest = 0;
    size_t direction = 0;
    for(size_t i = 0; i < 4; i++){
      double actual_value = result->get_position_value(0, i);
      if(actual_value > biggest){
        biggest = actual_value;
        direction = i;
      }
    }
    switch (direction) {
      case 0:
        player->direction_up();
        break;
      
      case 1:
        player->direction_down();
        break;

      case 2:
        player->direction_left();
        break;

      default:
        player->direction_right();
        break;
    }
  }

  void Population::update_player_direction(Player* player){
    this->nn->feedforward();
    this->get_new_direction(player);
  }

  Population::~Population(){
    delete[] this->individuals;
    delete this->nn;
  }

};
