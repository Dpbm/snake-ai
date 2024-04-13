#include <cstdint>
#include "ai_player.h"
#include "../../machine/weights.h"
#include "../../genetic/chromosome.h"

using Machine::Weights;
using Chromosomes::Chromosome;

namespace Players{
  AIPlayer::AIPlayer(uint8_t score_step, uint8_t board_w, uint8_t board_h){
    this->score_step = score_step;
    this->random_pos(board_w, board_h);
    this->random_dir();
    this->setup_nn();
  }

  void AIPlayer::setup_nn(){
    this->nn->add_layer(this->input_layer);
    this->nn->add_layer(4);
    this->nn->add_layer(4);

    this->nn->get_layer(1)->tanh(); 
    this->nn->get_output_layer()->softmax();
    this->setup_chromosome(); 
  }

  void AIPlayer::setup_chromosome(){
    uint32_t total_genes = 0;
    for(Weights* w : this->nn->get_weights())
      total_genes += (w->get_height() * w->get_width());

    this->chromosome = new Chromosome(total_genes); 
  }


  AIPlayer::~AIPlayer(){
    this->clear_pointers();
   
    delete this->chromosome;
    delete this->nn;
  }   

};
