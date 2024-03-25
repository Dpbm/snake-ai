#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include "ai_player.h"
#include "../../genetic/chromosome.h"
#include "../../matrix/matrix.h"
#include "../../machine/activation.h"
#include "../../helpers/utils.h"
#include "../../helpers/constants.h"
#include "../food.h"

using std::sqrt;
using std::pow;
using std::size_t;
using Chromosomes::Chromosome;
using Matrices::Matrix;
using Utils::random_int;
using Foods::Food;

namespace Players{
  AIPlayer::AIPlayer(){}
  
  void AIPlayer::setup_agent(uint8_t score_step, uint16_t max_score){ 
    this->randomize_position();
    this->randomize_direction();
    this->set_score_step(score_step);
    this->set_max_score(max_score);
    
    this->nn->add_layer(this->input_layer);
    this->nn->add_layer(4);
    this->nn->add_layer(4);
   
    this->nn->get_layer(1)->set_activation_function(Machine::tanh);
    this->nn->get_layer(2)->set_activation_function(Machine::softmax);
    this->input_layer->set_values(this->input_data);
    
    // get the chromosome_size based on the total weights
    uint16_t chromosome_size = 0;
    for(size_t weight_i = 0; weight_i < this->nn->get_total_weights(); weight_i++){
      Weights* weights = this->nn->get_weight(weight_i);
      chromosome_size += weights->get_width()*weights->get_height();
    }
      
    this->chromosome = new Chromosome(chromosome_size);
    
    // load the genes into the weights
    for(size_t weight_i = 0; weight_i < this->nn->get_total_weights(); weight_i++){
      uint8_t w = this->nn->get_weight(weight_i)->get_width();
      uint8_t h = this->nn->get_weight(weight_i)->get_height();

      this->nn->get_weight(weight_i)->load_weights(
        this->get_genes_matrix(w, h)
      );
    }
  }

  Directions AIPlayer::get_direction(){
    return this->direction;
  }

  void AIPlayer::randomize_direction(){
    Directions dir = (Directions)random_int(0,3);
    this->direction = dir;

    switch (dir) {
      case UP:
        this->direction_up();
        break;
      
      case DOWN:
        this->direction_down();
        break;
    
      case LEFT:
        this->direction_left();
        break;
      
      default:
        this->direction_right();
        break;    
    }
  }

  Food* AIPlayer::get_food(){
    return &this->food;
  }

  Matrix* AIPlayer::get_genes_matrix(unsigned int w, unsigned int h){
    Matrix* genes_matrix = new Matrix(w, h);
    int16_t gene_index = 0;
    for(size_t i = 0; i < h; i++)
      for(size_t j = 0; j < w; j++){
        genes_matrix->update_value(i, j, this->chromosome->get_genes()[gene_index].get_gene_value());        
        gene_index++;
      }

    return genes_matrix;
  }

  void AIPlayer::update_input_data(){
    int16_t fx = this->food.get_x(); 
    int16_t fy = this->food.get_y();
    double hip = sqrt(pow(fx-this->get_x(),2) + pow(this->get_y()-fy,2));
    double angle = hip == 0 ? 0 : acos(abs(fx-this->get_x())/hip); 

    if(fx > this->get_x() && fy > this->get_y())
      angle += (3*PI)/2;
    else if(fx < this->get_x() && fy < this->get_y())
      angle += PI/2;
    else if(fx < this->get_x() && fy > this->get_y())
      angle += PI;
    else if(fy == this->get_y() && this->get_x() < fx)
      angle = 0;
    else if(fy == this->get_y() && this->get_x() < fx)
      angle = PI;
    else if(this->get_x() == fx && this->get_y() > fy)
      angle = PI/2;
    else if(this->get_x() == fx && this->get_y() < fy)
      angle = (3*PI)/2;
    
    
    // this->input_data->update_value(0, 0, abs((LEFT_WALL-this->get_x())/(double)WIDTH));
    // this->input_data->update_value(0, 1, (WIDTH-this->get_x())/(double)PLAY_WIDTH);
    // this->input_data->update_value(0, 2, (this->get_y())/(double)HEIGHT);
    // this->input_data->update_value(0, 3, (HEIGHT-this->get_y())/(double)HEIGHT);
    this->input_data->update_value(0, 0, abs((this->get_x()-fx)/(double)PLAY_WIDTH));
    this->input_data->update_value(0, 1, abs((this->get_y()-fy)/(double)HEIGHT));
    this->input_data->update_value(0, 2, angle/(2*PI));
    // this->input_data->update_value(0, 3, (uint8_t)(this->direction != DOWN));
    // this->input_data->update_value(0, 4, (uint8_t)(this->direction != UP));
    // this->input_data->update_value(0, 5, (uint8_t)(this->direction != RIGHT));
    // this->input_data->update_value(0, 6, (uint8_t)(this->direction != LEFT));
  }
 

  
  Directions AIPlayer::get_new_direction(){
    this->nn->feedforward();
    Matrix* result = this->nn->get_output_layer()->get_values();
    // this->nn->get_layer(0)->get_values()->show(); 
    double biggest = 0;
    Directions direction = UP;
    for(size_t i = 0; i < 4; i++){
      double actual_value = result->get_position_value(0, i);
      if(actual_value > biggest){
        biggest = actual_value;
        direction = (Directions)i;
      }
    }

    return direction;
  }


  void AIPlayer::update_direction(Directions dir){
    this->direction = dir;
    switch (dir) {
      case UP:
        this->direction_up();
        break;
      
      case DOWN:
        this->direction_down();
        break;

      case LEFT:
        this->direction_left();
        break;

      default:
        this->direction_right();
        break;
    }
  }

  bool AIPlayer::is_trying_invalid_direction(Directions dir){
    return (this->direction == UP && dir == DOWN) || 
           (this->direction == DOWN && dir == UP) || 
           (this->direction == LEFT && dir == RIGHT) || 
           (this->direction == RIGHT && dir == LEFT);
  }

  Chromosome* AIPlayer::get_chromosome(){
    return this->chromosome;
  } 

  AIPlayer::~AIPlayer(){
    delete this->chromosome;
    delete this->nn;
  }
};
