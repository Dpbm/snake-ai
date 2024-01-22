#include "matrix.h"
#include <iostream>
#include <sched.h>

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
  
  Matrix::Matrix(unsigned int width, unsigned int height){
    this->height = height;
    this->width = width;

    this->matrix = new double*[height];
    for(unsigned int i = 0; i < height; i++)
      this->matrix[i] = new double[width];
  }

  double** Matrix::get_matrix(){
    return this->matrix;
  }

  void Matrix::zeros(){
    for(unsigned int i = 0; i < this->height; i++)
      for(unsigned int j = 0; j < this->width; j++)
        this->update_value(i, j, 0);
  }

  void Matrix::update_value(unsigned int i, unsigned int j, double value){
    if(i > this->height || j > this->width)
      throw std::invalid_argument("i and j must be a value within the bounds of the matrix"); 

    this->matrix[i][j] = value;
  }
  
  double Matrix::get_position_value(unsigned int i, unsigned int j){
    return this->matrix[i][j];
  }

  // Maybe its a better idea to push it to heap
  // however, when I do a copy, my Idea is:
  // Matrices::Matrix old_matrix = old_matrix*5;
  // So cleaning the memory from old_matrix*5, could be a little trickier 
  Matrices::Matrix Matrix::copy(){
    Matrices::Matrix clone_matrix(this->width, this->height);
    for(int i = 0; i < this->height; i++)
      for(int j = 0; j < this->width; j++)
        clone_matrix.update_value(i, j, this->get_position_value(i, j));
    return clone_matrix;
  }

  Matrices::Matrix Matrix::operator *(int scalar){
    Matrices::Matrix clone_matrix = this->copy();
    for(int i = 0; i < this->height; i++)
      for(int j = 0; j < this->width; j++)
        clone_matrix.update_value(i, j, scalar * clone_matrix.get_position_value(i, j));      
    return clone_matrix;
  }
}
