#include "weights.h"
#include "../matrix/matrix.h"
#include <sstream>
#include "../helpers/utils.h"

using Matrices::Matrix;
using Matrices::MatrixRandomTemplate;
using std::string;
using std::stringstream;
using Utils::append_to_file;

namespace NNWeights {
  unsigned int width, height;
  template <typename T> Matrix<MatrixWeightsTemplate<T>> *weights;

  template <typename T> Weights<T>::Weights(unsigned int first_layer_size, unsigned int second_layer_size){
    this->width = first_layer_size;
    this->height = second_layer_size;
    this->weights = new Matrix<MatrixRandomTemplate<T>>(first_layer_size, second_layer_size);
    this->weights->random(-1, 1);
  }

  template <typename T> void Weights<T>::load_weights(Matrix<MatrixWeightsTemplate<T>> * weights){
    this->Weights::clear_pointers();
    this->width = weights->get_width();
    this->height = weights->get_height();
    this->weights = weights;
  }

  template <typename T> void Weights<T>::save_weights(string filename){
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

  template <typename T> Matrix<MatrixWeightsTemplate<T>> *Weights<T>::get_weights(){
    return this->weights;
  }

  template <typename T> void Weights<T>::clear_pointers(){
    delete this->weights;
  }

  template <typename T> Weights<T>::~Weights(){ 
    this->Weights::clear_pointers();
  }

  template <typename T> unsigned int Weights<T>::get_height(){
    return this->height;
  }
  
  template <typename T> unsigned int Weights<T>::get_width(){
    return this->width;
  }
}
