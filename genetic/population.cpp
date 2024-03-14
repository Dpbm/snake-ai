#include <cstddef>
#include <cstdint>
#include <iostream>
#include "population.h"
#include "ai_player.h"
#include "../machine/activation.h"
#include "../game/player.h"
#include "../helpers/constants.h"
#include "../helpers/utils.h"
#include "chromosome.h"
#include "gene.h"

using AIAgent::AIPlayer;
using Players::Player;
using Chromosomes::Chromosome;
using Utils::random_int;
using Genes::Gene;

namespace Populations{

  Population::Population(uint8_t total){
    this->individuals = new AIPlayer[total];
    this->total_individuals = total;
    this->distances = new uint16_t[total];
    this->points = new int16_t[total];
    this->setup_nn();
    this->get_nn_total_weights();

    for(size_t i = 0; i < total; i++)
      this->individuals[i].setup_choromosome(this->total_weights);
    this->load_genes_into_weights();
  }

  void Population::setup_nn(){
    this->nn->add_layer(this->input_layer);
    this->nn->add_layer(4);
    this->nn->add_layer(4);
    
    this->nn->get_layer(1)->set_activation_function(Activations::tanh);
    this->nn->get_layer(2)->set_activation_function(Activations::softmax);
    this->input_layer->set_values(this->input_data);
  }

  void Population::get_nn_total_weights(){
    uint16_t genes_array_size = 0;
    for(size_t weight_i = 0; weight_i < this->nn->get_total_weights(); weight_i++){
      uint8_t w = this->nn->get_weight(weight_i)->get_width();
      uint8_t h = this->nn->get_weight(weight_i)->get_height();
      genes_array_size += w*h;
    }
    this->total_weights = genes_array_size;
  }

  void Population::load_genes_into_weights(){
    for(size_t weight_i = 0; weight_i < this->nn->get_total_weights(); weight_i++){
      uint8_t w = this->nn->get_weight(weight_i)->get_width();
      uint8_t h = this->nn->get_weight(weight_i)->get_height();

      this->nn->get_weight(weight_i)->load_weights(
        this->individuals[this->actual_individual].get_genes_matrix(w, h)
      );
    }
  }
  
  void Population::next_generation(){
    int16_t fitness[this->total_individuals];
  
    // uint16_t closest_distance = (uint16_t)10000;
    // size_t indiv_closest_distance = 0;
    // size_t second_indiv_closest_distance = 1;
    // for(size_t i = 0; i < this->total_individuals; i++){
    //   if(this->distances[i] <= closest_distance){
    //     closest_distance = this->distances[i];
    //     size_t tmp = indiv_closest_distance;
    //     indiv_closest_distance = i;
    //     second_indiv_closest_distance = tmp;
    //   }
    // }
   

    for(size_t i = 0; i < this->total_individuals; i++){
      fitness[i] = 0;

      if(this->points[i] == 0){
        fitness[i] += -10000;
      }else{
        fitness[i] += this->points[i]*100;
      }

      if(this->distances[i] >= 200){
        fitness[i] += -10000;
      }else{
        fitness[i] += 1000;
      }
    }

    for(size_t i = 0; i < this->total_individuals; i++){
      std::cout << fitness[i] << " ";
    }
    std::cout << "\n\n";

    size_t best_p1 = 0;
    int16_t best_f1 = 0;
    for(size_t i = 0; i < this->total_individuals; i++){
      if(fitness[i] > best_f1){
        best_p1 = i;
        best_f1 = fitness[i];
      }
    }
    

    size_t best_p2 = 0;
    int16_t best_f2 = 0;
    for(size_t i = 0; i < this->total_individuals; i++){
      if(fitness[i] >= best_f2 && i != best_p1){
        best_p2 = i;
        best_f2 = fitness[i];
      }
    }

    Chromosome* indiv1 = this->individuals[best_p1].get_chromosome();
    Chromosome* indiv2 = this->individuals[best_p2].get_chromosome();
    uint8_t chromosome_pivot = random_int(0, this->total_weights-1);

    Chromosome* offspring = new Chromosome(this->total_weights);
    
    Gene* offspring_genes = offspring->get_genes();
    Gene* indiv1_genes = indiv1->get_genes();
    Gene* indiv2_genes = indiv2->get_genes();

    for(size_t i = 0; i < this->total_weights; i++){
      if(i <= chromosome_pivot)
        offspring_genes[i].set_gene_value(indiv1_genes[i].get_gene_value());
      else
        offspring_genes[i].set_gene_value(indiv2_genes[i].get_gene_value());
    }

    for(size_t i = 0; i < this->total_individuals; i++){
      Chromosome* actual_individual_chromosome = this->individuals[i].get_chromosome();
      if(i == best_p1 || i == best_f2){
        actual_individual_chromosome->mutate(0.03);  
        continue;
      }
      actual_individual_chromosome->copy_genes(offspring_genes);
      actual_individual_chromosome->mutate(0.1);
    }
    delete offspring;
  }
  

  void Population::update_input_data(uint16_t px, uint16_t py, uint16_t fx, uint16_t fy){
    double hip = sqrt(pow(fx-px,2) + pow(py-fy,2));
    double angle = hip == 0 ? 0 : acos(abs(fx-px)/hip); 

    if(fx > px && fy > py)
      angle += (3*PI)/2;
    else if(fx < px && fy < py)
      angle += PI/2;
    else if(fx < px && fy > py)
      angle += PI;
    else if(fy == py && px < fx)
      angle = 0;
    else if(fy == py && px < fx)
      angle = PI;
    else if(px == fx && py > fy)
      angle = PI/2;
    else if(px == fx && py < fy)
      angle = (3*PI)/2;
    
    
    this->input_data->update_value(0, 0, (fx-px)%50);
    this->input_data->update_value(0, 1, (fy-py)%50);
    this->input_data->update_value(0, 2, (angle));
  }

  uint8_t Population::get_actual_individual(){
    return this->actual_individual;
  }

  void Population::add_points(int16_t points){
    this->points[this->actual_individual] = points;
  }

  void Population::add_distance(uint16_t distance){
    this->distances[this->actual_individual] = distance;
  }
  
  void Population::reset_individual(){
    this->actual_individual=0;
  }

  void Population::update_actual_individual(){
    this->actual_individual ++;
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
    delete[] this->distances;
    delete[] this->points;
    delete this->nn;
  }

};
