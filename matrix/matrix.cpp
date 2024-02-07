#include <iostream>
#include <sched.h>
#include <stdexcept>
#include "matrix.h"
#include "../helpers/utils.h"

namespace Matrices{
  unsigned int width, height;
  template <typename T> MatrixTemplate<T>** matrix;

  template <typename T> Matrix<MatrixTemplate<T>>::Matrix(unsigned int length){
    this->width = length;
    this->height = length;
    this->matrix = this->generate_matrix_body(length, length);
  }
  
  template <typename T> Matrix<MatrixTemplate<T>>::Matrix(unsigned int width, unsigned int height){
    this->height = height;
    this->width = width;
    this->matrix = this->generate_matrix_body(width, height);
  }

  template <typename T> MatrixTemplate<T>** Matrix<MatrixTemplate<T>>::get_matrix(){
    return this->matrix;
  }
  
  template <typename T> void Matrix<MatrixTemplate<T>>::map_to_a_single_value(MatrixTemplate<T> value){
    for(unsigned int i = 0; i < this->height; i++)
      for(unsigned int j = 0; j < this->width; j++)
        this->update_value(i, j, value);
  }
  
  template<typename T> void Matrix<MatrixRandomTemplate<T>>::random(int start, int end){
    for(unsigned int i = 0; i < this->height; i++)
      for(unsigned int j = 0; j < this->width; j++)
        this->update_value(i, j, Utils::random(start, end)); 
  }

  template<typename T> void Matrix<MatrixTemplate<T>>::update_value(unsigned int i, unsigned int j, MatrixTemplate<T> value){
    if(i >= this->height || j >= this->width)
      throw std::invalid_argument("i and j must be a value within the bounds of the matrix"); 

    this->matrix[i][j] = value;
  }
  
  template <typename T> MatrixTemplate<T> Matrix<MatrixTemplate<T>>::get_position_value(unsigned int i, unsigned int j) const {
    if(i >= this->height || j >= this->width) 
      throw std::invalid_argument("i and j must be a value within the bounds of the matrix");

    return this->matrix[i][j];
  }

  // Maybe its a better idea to push it to heap
  // however, when I do a copy, my Idea is:
  // Matrices::Matrix old_matrix = old_matrix*5;
  // So cleaning the memory from old_matrix*5, could be a little trickier 
  template<typename T> Matrix<MatrixTemplate<T>> Matrix<MatrixTemplate<T>>::copy(){
    Matrix<MatrixTemplate<T>> clone_matrix(this->width, this->height);
    for(unsigned int i = 0; i < this->height; i++)
      for(unsigned int j = 0; j < this->width; j++)
        clone_matrix.update_value(i, j, this->get_position_value(i, j));
    return clone_matrix;
  }

  template <typename T> Matrix<MatrixTemplate<T>> Matrix<MatrixTemplate<T>>::operator *(MatrixTemplate<T> scalar){
    Matrix<MatrixTemplate<T>> clone_matrix = this->copy();
    for(unsigned int i = 0; i < this->height; i++)
      for(unsigned int j = 0; j < this->width; j++)
        clone_matrix.update_value(i, j, scalar * clone_matrix.get_position_value(i, j));      
    return clone_matrix;
  }

  template <typename T> void Matrix<MatrixTemplate<T>>::operator=(const Matrix<MatrixTemplate<T>>& another_matrix){
    for(unsigned int i = 0; i < this->height; i++)
      for(unsigned int j = 0; j < this->width; j++)
        this->update_value(i, j, another_matrix.get_position_value(i,j));
    
    // could add a delete for a matrix pointer here
  }

  template <typename T> unsigned int Matrix<MatrixTemplate<T>>::get_height() const{
    return this->height;
  }
  
  template <typename T> unsigned int Matrix<MatrixTemplate<T>>::get_width() const{
    return this->width;
  }
  
  template <typename T> MatrixTemplate<T>* Matrix<MatrixTemplate<T>>::get_row(unsigned int i) const{
    MatrixTemplate<T>* row = new MatrixTemplate<T>[this->width];
    for(unsigned int j = 0; j < this->width; j++)
      row[j] = this->get_position_value(i, j);
    return row;
  }
  
  template <typename T> MatrixTemplate<T>* Matrix<MatrixTemplate<T>>::get_column(unsigned int j) const{
    MatrixTemplate<T>* column = new MatrixTemplate<T>[this->height];
    for(unsigned int i = 0; i < this->height; i++)
      column[i] = this->get_position_value(i, j);
    return column;
  }

  template <typename T> Matrix<MatrixTemplate<T>> Matrix<MatrixTemplate<T>>::operator *(const Matrix<MatrixTemplate<T>>& another_matrix){
    if(this->width != another_matrix.get_height())
      throw std::invalid_argument("The first matrix's width must be equal to the second's height!");
    
    // here's also a better idea to instanciate in the heap
    unsigned int second_matrix_width = another_matrix.get_width();
    Matrix<MatrixTemplate<T>> resulting_matrix(second_matrix_width, this->height);

    for(unsigned int i = 0; i < this->height; i++){
      MatrixTemplate<T>* row = this->get_row(i);
      
      for(unsigned int j = 0; j < second_matrix_width; j++){
        MatrixTemplate<T>* column = another_matrix.get_column(j);
      
        MatrixTemplate<T> value = 0;
        for(unsigned int n_index = 0; n_index < this->width; n_index++)
          value += row[n_index]*column[n_index];

        resulting_matrix.update_value(i, j, value);
        delete column;
      }  
      delete row;
    }
    
    return resulting_matrix;
  }

  template <typename T> void Matrix<MatrixTemplate<T>>::show(){
    for(unsigned int i = 0; i < this->height; i++){
      for(unsigned int j = 0; j < this->width; j++)
        std::cout << this->get_position_value(i, j) << " "; 
      std::cout << "" << std::endl;
    }
  }

  template <typename T> Matrix<MatrixTemplate<T>>::~Matrix(){
    this->Matrix::clear_pointers();
  }
  
  template <typename T> void Matrix<MatrixTemplate<T>>::transpose(){
    MatrixTemplate<T>** transposed_matrix = this->Matrix::generate_matrix_body(this->height, this->width);  

    for(unsigned int i = 0; i < this->height; i++)
      for(unsigned int j = 0; j < this->width; j++)
        transposed_matrix[j][i] = this->Matrix::get_position_value(i, j);
    
    unsigned int tmp = this->height;
    this->height = this->width;
    this->width = tmp;

    this->Matrix::clear_pointers();
    this->matrix = transposed_matrix;
  }

  template <typename T> void Matrix<MatrixTemplate<T>>::clear_pointers(){
    for(unsigned int i = 0; i < this->height; i++)
      delete this->matrix[i];
    delete this->matrix;  
  }

  template <typename T> MatrixTemplate<T> **Matrix<MatrixTemplate<T>>::generate_matrix_body(unsigned int width, unsigned int height){
    MatrixTemplate<T>** new_matrix = new MatrixTemplate<T>*[height];
    for(unsigned int i = 0; i<height; i++)
      new_matrix[i] = new MatrixTemplate<T>[width];

    return new_matrix;
  }
}
