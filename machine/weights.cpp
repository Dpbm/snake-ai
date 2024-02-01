#include "weights.h"
#include "../matrix/matrix.h"
#include <iostream>
#include <sstream>
#include "../helpers/utils.h"

using Matrices::Matrix;
using std::string;
using std::stringstream;
using Utils::append_to_file;

namespace NNWeights {
  unsigned int width, height;
  Matrix *weights;

  Weights::Weights(unsigned int first_layer_size, unsigned int second_layer_size){
    this->width = first_layer_size;
    this->height = second_layer_size;
    this->weights = new Matrix(first_layer_size, second_layer_size);
    this->weights->random(-1, 1);
  }

  void Weights::load_weights(Matrix* weights){
    this->Weights::clear_pointers();
    this->width = weights->get_width();
    this->height = weights->get_height();
    this->weights = weights;
  }

  void Weights::save_weights(string filename){
    stringstream header;
    header << "w:" << this->width << ";h:" << this->height  << "\n"; 
    
    append_to_file(filename, header.str());

    for(unsigned int i = 0; i < this->height; i++){
      for(unsigned int j = 0; j < this->width; j++){
        stringstream data;
        data << this->weights->get_position_value(i, j) << (j < this->width-1 ? "," : "");
        append_to_file(filename, data.str());
      }

      append_to_file(filename, "\n");
    }
  }

  Matrix *Weights::get_weights(){
    return this->weights;
  }

  void Weights::clear_pointers(){
    delete this->weights;
  }

  Weights::~Weights(){ 
    this->Weights::clear_pointers();
  }

  unsigned int Weights::get_height(){
    return this->height;
  }
  
  unsigned int Weights::get_width(){
    return this->width;
  }
}
