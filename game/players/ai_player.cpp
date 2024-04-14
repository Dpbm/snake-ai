#include <cstdint>
#include "ai_player.h"
#include "../../machine/weights.h"
#include "../../genetic/chromosome.h"

using Machine::Weights;
using Chromosomes::Chromosome;

namespace Players{
  AIPlayer::AIPlayer(uint8_t score_step, uint8_t board_w, uint8_t board_h){
    this->set_score_step(score_step);
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
    this->load_genes_into_weights();
  }

  void AIPlayer::setup_chromosome(){
    uint64_t total_genes = 0;
    for(Weights* w : this->nn->get_weights())
      total_genes += w->get_total_weights();

    this->chromosome = new Chromosome(total_genes); 
  }

  void AIPlayer::load_genes_into_weights(){
    uint64_t last_index = 0;

    for(Weights* w : this->nn->get_weights()){
      Matrix* genes_m = new Matrix(w->get_width(), w->get_height());
    

      Gene** genes = this->chromosome->slice(last_index, last_index + w->get_total_weights());
      last_index += w->get_total_weights();
 
      uint64_t gene_i = 0;
      for(size_t i = 0; i < w->get_height(); i++)
        for(size_t j = 0; j < w->get_width(); j++)
          genes_m->update_value(i, j, genes[gene_i++]->get_gene_value());
      
      delete[] genes;
    }
  }


  AIPlayer::~AIPlayer(){
    this->clear_pointers();
   
    delete this->chromosome;
    delete this->nn;
  }   

};
