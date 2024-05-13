#include <ctime>
#include <cstdint>
#include <sstream>
#include <string>
#include "ai_player.h"
#include "../../machine/weights.h"
#include "../../genetic/chromosome.h"
#include "../../helpers/utils.h"
#include "../../matrix/matrix.h"
#include "player.h"

using std::to_string;
using std::stringstream;
using Machine::Weights;
using Genetic::Chromosome;
using Utils::vec2;
using Matrices::Matrix;

namespace Players{
  AIPlayer::AIPlayer(uint8_t board_w, uint8_t board_h) : Player(board_w, board_h){
    this->setup_nn();
    this->setup_chromosome(); 
    this->load_genes_into_weights();
  }
  
  AIPlayer::AIPlayer(uint8_t board_w, uint8_t board_h, Chromosome* chromosome) : Player(board_w, board_h){
    this->setup_nn();
    this->chromosome = chromosome;
    this->load_genes_into_weights();
  }
  
  AIPlayer::AIPlayer(uint8_t board_w, uint8_t board_h, NN* nn) : Player(board_w, board_h){
    this->nn = nn;
    this->chromosome = nullptr;
  }

  void AIPlayer::setup_nn(){
    this->nn->add_layer(2);
    this->nn->add_layer(4);
    this->nn->add_layer(4);

    this->nn->get_layer(1)->relu(); 
    this->nn->get_output_layer()->softmax();
  }

  void AIPlayer::setup_chromosome(){
    uint64_t total_genes = 0;
    for(Weights* w : this->nn->get_weights())
      total_genes += w->get_total_weights();

    this->chromosome = new Chromosome(total_genes); 
  }

  Chromosome* AIPlayer::get_chromossome(){
    return this->chromosome;
  }

  void AIPlayer::load_genes_into_weights(){
    uint64_t last_index = 0;

    for(Weights* w : this->nn->get_weights()){
      Matrix* genes_m = new Matrix(w->get_width(), w->get_height());
      uint64_t total_weights = w->get_total_weights();

      Gene** genes = this->chromosome->slice(last_index, last_index + total_weights);
      last_index += total_weights;
 
      uint64_t gene_i = 0;
      for(size_t i = 0; i < w->get_height(); i++)
        for(size_t j = 0; j < w->get_width(); j++)
          genes_m->update_value(i, j, genes[gene_i++]->get_gene_value());

      w->load_weights(genes_m);
      delete[] genes;
    }
  }

  void AIPlayer::update_input_data(const vec2& food, uint16_t w, uint16_t h){
    int16_t px = this->get_x();
    int16_t py = this->get_y();
    int16_t fx = food.x;
    int16_t fy = food.y;

    Matrix* input = this->nn->get_input_layer()->get_values();
    input->update_value(0, 0, (double)(px-fx)/w);
    input->update_value(0, 1, (double)(py-fy)/h);
  }


  void AIPlayer::compute_next_dir(){
    this->nn->feedforward();
  }

  void AIPlayer::update_dir(){
    Matrix* output = this->nn->get_output_layer()->get_values();
    size_t new_dir = 0;
    double biggest = 0;
    for(size_t i = 0; i < 4; i++){
      double value = output->get_position_value(0, i);

      if(value > biggest){
        biggest = value;
        new_dir = i;
      }
    }
    
    this->set_dir((Directions)new_dir);
  }

  void AIPlayer::save_weights(){
    time_t now = time(0);
    string time = asctime(localtime(&now));
    //remove the $\n at the end of the string
    time.pop_back();
    
    stringstream filename;
    filename << time;
    filename << ".wg"; 
    this->nn->save_weights(filename.str());
  }
  
  void AIPlayer::save_weights(uint32_t gen){
    time_t now = time(0);
    string time = asctime(localtime(&now));
    //remove the $\n at the end of the string
    time.pop_back();
    
    stringstream filename;
    filename << time;
    filename << "gen-";
    filename << to_string(gen);
    filename << ".wg"; 
    this->nn->save_weights(filename.str());
  }

  AIPlayer::~AIPlayer(){
    delete this->chromosome;
    delete this->nn;
  }   

};
