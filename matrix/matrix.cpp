#include "matrix.h"

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

}
