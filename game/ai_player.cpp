#include <cmath>
#include <cstddef>
#include "ai_player.h"
#include "../genetic/chromosome.h"
#include "../matrix/matrix.h"
#include "../helpers/constants.h"

using std::sqrt;
using std::pow;
using std::acos;
using std::abs;
using std::size_t;
using Chromosomes::Chromosome;
using Matrices::Matrix;

namespace Players{
  Players::AIPlayer(){}

  void Players::setup_choromosome(unsigned int chromosome_size){
    this->chromosome = new Chromosome(chromosome_size);
  }

  Matrix* Players::get_genes_matrix(unsigned int w, unsigned int h){
    Matrix* genes_matrix = new Matrix(w, h);

    int gene_index = 0;
    for(size_t i = 0; i < h; i++)
      for(size_t j = 0; j < w; j++){
        genes_matrix->update_value(i, j, this->chromosome->get_genes()[gene_index].get_gene_value());        
        gene_index++;
      }

    return genes_matrix;
  }

  Chromosome* Players::get_chromosome(){
    return this->chromosome;
  } 

  
  void Players::update_input_data(Matrix* input_data, uint16_t px, uint16_t py, uint16_t fx, uint16_t fy){
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
    
    input_data->update_value(0, 0, (fx-px)%50);
    input_data->update_value(0, 1, (fy-py)%50);
    input_data->update_value(0, 2, (angle));
  }

  Players::~AIPlayer(){
    delete this->chromosome;
  }
};
