#include "matrix.h"
#include <iostream>
#include <stdexcept>

namespace Matrices{
  unsigned int width, height;
  double** matrix;

  Matrix::Matrix(unsigned int length){
    this->width = length;
    this->height = length;

    this->matrix = new double*[length];
    for(unsigned int i = 0; i<length; i++)
      this->matrix[i] = new double[length];
  }
  
  Matrix::Matrix(unsigned int input_width, unsigned int input_height){
    this->height = input_height;
    this->width = input_width;

    this->matrix = new double*[input_height];
    for(unsigned int i = 0; i < input_height; i++)
      this->matrix[i] = new double[input_width];
  }

  double** Matrix::get_matrix(){
    return this->matrix;
  }

  void Matrix::zeros(){
    for(unsigned int i = 0; i < this->height; i++)
      for(unsigned int j = 0; j < this->width; j++)
        this->matrix[i][j] = 0;
  }

  void Matrix::update_value(unsigned int i, unsigned int j, double value){
    if(i > this->height || j > this->width)
      throw std::invalid_argument("i and j must be a value within the bounds of the matrix"); 

    this->matrix[i][j] = value;
  }

}
