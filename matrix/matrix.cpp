#include <cstddef>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include "matrix.h"

using std::size_t;
using std::invalid_argument;

namespace Matrices{
  Matrix::Matrix(uint16_t length){
    this->width = length;
    this->height = length;
    this->matrix = this->generate_matrix_body();
  }
  
  Matrix::Matrix(uint16_t width, uint16_t height){
    this->height = height;
    this->width = width;
    this->matrix = this->generate_matrix_body();
  }

  double** Matrix::get_matrix(){
    return this->matrix;
  }
  
  void Matrix::map_to_a_single_value(double value){
    for(size_t i = 0; i < this->height; i++)
      for(size_t j = 0; j < this->width; j++)
        this->update_value(i, j, value);
  }
 
  void Matrix::update_value(uint16_t i, uint16_t j, double value){
    if(i >= this->height || j >= this->width)
      throw invalid_argument("i and j must be a value within the bounds of the matrix"); 
    this->matrix[i][j] = value;
  }

  double Matrix::get_position_value(uint16_t i, uint16_t j) const {
    if(i >= this->height || j >= this->width) 
      throw invalid_argument("i and j must be a value within the bounds of the matrix");
    return this->matrix[i][j];
  }
  
  uint16_t Matrix::get_height() const{
    return this->height;
  }
  
  uint16_t Matrix::get_width() const{
    return this->width;
  }
  
  double* Matrix::get_row(uint16_t i) const{
    // REMEMBER TO DEALLOCATE AFTER USING THE RETURNED ROW
    double* row = new double[this->width];
    for(size_t j = 0; j < this->width; j++)
      row[j] = this->get_position_value(i, j);
    return row;
  }
  
  double* Matrix::get_column(uint16_t j) const{
    // REMEMBER TO DEALLOCATE AFTER USING THE RETURNED COLUMN
    double* column = new double[this->height];
    for(size_t i = 0; i < this->height; i++)
      column[i] = this->get_position_value(i, j);
    return column;
  }

  Matrix* Matrix::operator *(const Matrix& another_matrix){
    if(this->width != another_matrix.get_height())
      throw invalid_argument("The first matrix's width must be equal to the second's height!");
    
    uint16_t second_matrix_width = another_matrix.get_width();
    Matrix* resulting_matrix = new Matrix(second_matrix_width, this->height);

    for(size_t i = 0; i < this->height; i++){
      double* row = this->get_row(i);
      
      for(size_t j = 0; j < second_matrix_width; j++){
        double* column = another_matrix.get_column(j);
      
        double value = 0;
        for(size_t n_index = 0; n_index < this->width; n_index++)
          value += row[n_index]*column[n_index];

        resulting_matrix->update_value(i, j, value);
        delete[] column;
      }  
      delete[] row;
    }
    
    return resulting_matrix;
  }

  void Matrix::show(){
    for(size_t i = 0; i < this->height; i++){
      for(size_t j = 0; j < this->width; j++)
        std::cout << this->matrix[i][j] << " "; 
      std::cout << "" << std::endl;
    }
  }

  Matrix::~Matrix(){
    for(size_t i = 0; i < this->height; i++)
      delete[] this->matrix[i];
    delete[] this->matrix;
  }
  
  double** Matrix::generate_matrix_body(){
    double** new_matrix = new double*[this->height];
    for(size_t i = 0; i < this->height; i++)
      new_matrix[i] = new double[this->width];
    return new_matrix;
  } 
}
