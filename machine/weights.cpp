#include "weights.h"
#include "../matrix/matrix.h"
#include <iostream>
#include <fstream>

using Matrices::Matrix;
using std::ofstream;
using std::string;

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
    ofstream file(filename);

    if(file.is_open()){
      file << "w:" << this->width << ";h:" << this->height  << "\n";

      for(unsigned int i = 0; i < this->height; i++){
        for(unsigned int j = 0; j < this->width; j++)
          file << this->weights->get_position_value(i, j) << (j < this->width-1 ? "," : "");
        file << "\n";
      }

      file.close();
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
