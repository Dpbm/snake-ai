#include "matrix.h"
#include <iostream>
#include <sched.h>
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
    if(i >= this->height || j >= this->width)
      throw std::invalid_argument("i and j must be a value within the bounds of the matrix"); 

    this->matrix[i][j] = value;
  }
  
  double Matrix::get_position_value(unsigned int i, unsigned int j) const {
    if(i >= this->height || j >= this->width) 
      throw std::invalid_argument("i and j must be a value within the bounds of the matrix");

    return this->matrix[i][j];
  }

  // Maybe its a better idea to push it to heap
  // however, when I do a copy, my Idea is:
  // Matrices::Matrix old_matrix = old_matrix*5;
  // So cleaning the memory from old_matrix*5, could be a little trickier 
  Matrices::Matrix Matrix::copy(){
    Matrices::Matrix clone_matrix(this->width, this->height);
    for(unsigned int i = 0; i < this->height; i++)
      for(unsigned int j = 0; j < this->width; j++)
        clone_matrix.update_value(i, j, this->get_position_value(i, j));
    return clone_matrix;
  }

  Matrices::Matrix Matrix::operator *(int scalar){
    Matrices::Matrix clone_matrix = this->copy();
    for(unsigned int i = 0; i < this->height; i++)
      for(unsigned int j = 0; j < this->width; j++)
        clone_matrix.update_value(i, j, scalar * clone_matrix.get_position_value(i, j));      
    return clone_matrix;
  }

  void Matrix::operator=(const Matrices::Matrix& another_matrix){
    for(unsigned int i = 0; i < this->height; i++)
      for(unsigned int j = 0; j < this->width; j++)
        this->update_value(i, j, another_matrix.get_position_value(i,j));
    
    // could add a delete for a matrix pointer here
  }

  unsigned int Matrix::get_height() const{
    return this->height;
  }
  
  unsigned int Matrix::get_width() const{
    return this->width;
  }
  
  double* Matrix::get_row(unsigned int i) const{
    double* row = new double[this->width];
    for(unsigned int j = 0; j < this->width; j++)
      row[j] = this->get_position_value(i, j);
    return row;
  }
  
  double* Matrix::get_column(unsigned int j) const{
    double* column = new double[this->height];
    for(unsigned int i = 0; i < this->height; i++)
      column[i] = this->get_position_value(i, j);
    return column;
  }

  Matrices::Matrix Matrix::operator *(const Matrices::Matrix& another_matrix){
    if(this->width != another_matrix.get_height())
      throw std::invalid_argument("The first matrix's width must be equal to the second's height!");
   
    unsigned int second_matrix_width = another_matrix.get_width();
    Matrices::Matrix resulting_matrix(second_matrix_width, this->height);

    for(unsigned int i = 0; i < this->height; i++){
      double *row = this->get_row(i);
      
      for(unsigned int j = 0; j < second_matrix_width; j++){
        double *column = another_matrix.get_column(j);
      
        double value = 0;
        for(unsigned int n_index = 0; n_index < this->width; n_index++)
          value += row[n_index]*column[n_index];

        resulting_matrix.update_value(i, j, value);
        delete column;
      }  
      delete row;
    }
    
    return resulting_matrix;
  }

  void Matrix::show(){
    for(int i = 0; i < this->height; i++){
      for(int j = 0; j < this->width; j++)
        std::cout << this->get_position_value(i, j) << " "; 
      std::cout << "" << std::endl;
    }
  }
}
