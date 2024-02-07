#include <iostream>
#include <sched.h>
#include <stdexcept>
#include "matrix.h"
#include "../helpers/utils.h"

using Matrices::MatrixOfNumbersTemplate;

namespace Matrices{
  unsigned int width, height;
  template <typename T> T** matrix;

  template <typename T> Matrix<T>::Matrix(unsigned int length){
    this->width = length;
    this->height = length;
    this->matrix = this->generate_matrix_body(length, length);
  }
  
  template <typename T> Matrix<T>::Matrix(unsigned int width, unsigned int height){
    this->height = height;
    this->width = width;
    this->matrix = this->generate_matrix_body(width, height);
  }

  template <typename T> T** Matrix<T>::get_matrix(){
    return this->matrix;
  }
  
  template <typename T> void Matrix<T>::map_to_a_single_value(T value){
    for(unsigned int i = 0; i < this->height; i++)
      for(unsigned int j = 0; j < this->width; j++)
        this->update_value(i, j, value);
  }
  
  template<typename T> void Matrix<MatrixOfNumbersTemplate<T>>::random(int start, int end){
    for(unsigned int i = 0; i < this->height; i++)
      for(unsigned int j = 0; j < this->width; j++)
        this->update_value(i, j, Utils::random(start, end)); 
  }

  template<typename T> void Matrix<T>::update_value(unsigned int i, unsigned int j, T value){
    if(i >= this->height || j >= this->width)
      throw std::invalid_argument("i and j must be a value within the bounds of the matrix"); 

    this->matrix[i][j] = value;
  }
  
  template <typename T> T Matrix<T>::get_position_value(unsigned int i, unsigned int j) const {
    if(i >= this->height || j >= this->width) 
      throw std::invalid_argument("i and j must be a value within the bounds of the matrix");

    return this->matrix[i][j];
  }

  // Maybe its a better idea to push it to heap
  // however, when I do a copy, my Idea is:
  // Matrices::Matrix old_matrix = old_matrix*5;
  // So cleaning the memory from old_matrix*5, could be a little trickier 
  template<typename T> Matrix<T> Matrix<T>::copy(){
    Matrix<T> clone_matrix(this->width, this->height);
    for(unsigned int i = 0; i < this->height; i++)
      for(unsigned int j = 0; j < this->width; j++)
        clone_matrix.update_value(i, j, this->get_position_value(i, j));
    return clone_matrix;
  }

  template <typename T> Matrix<MatrixOfNumbersTemplate<T>> Matrix<MatrixOfNumbersTemplate<T>>::operator *(MatrixOfNumbersTemplate<T> scalar){
    Matrix<MatrixOfNumbersTemplate<T>> clone_matrix = this->copy();
    for(unsigned int i = 0; i < this->height; i++)
      for(unsigned int j = 0; j < this->width; j++)
        clone_matrix.update_value(i, j, scalar * clone_matrix.get_position_value(i, j));      
    return clone_matrix;
  }

  template <typename T> void Matrix<T>::operator=(const Matrix<T>& another_matrix){
    for(unsigned int i = 0; i < this->height; i++)
      for(unsigned int j = 0; j < this->width; j++)
        this->update_value(i, j, another_matrix.get_position_value(i,j));
    
    // could add a delete for a matrix pointer here
  }

  template <typename T> unsigned int Matrix<T>::get_height() const{
    return this->height;
  }
  
  template <typename T> unsigned int Matrix<T>::get_width() const{
    return this->width;
  }
  
  template <typename T> T* Matrix<T>::get_row(unsigned int i) const{
    T* row = new T[this->width];
    for(unsigned int j = 0; j < this->width; j++)
      row[j] = this->get_position_value(i, j);
    return row;
  }
  
  template <typename T> T* Matrix<T>::get_column(unsigned int j) const{
    T* column = new T[this->height];
    for(unsigned int i = 0; i < this->height; i++)
      column[i] = this->get_position_value(i, j);
    return column;
  }

  template <typename T> Matrix<MatrixOfNumbersTemplate<T>> Matrix<MatrixOfNumbersTemplate<T>>::operator *(const Matrix<MatrixOfNumbersTemplate<T>>& another_matrix){
    if(this->width != another_matrix.get_height())
      throw std::invalid_argument("The first matrix's width must be equal to the second's height!");
    
    // here's also a better idea to instanciate in the heap
    unsigned int second_matrix_width = another_matrix.get_width();
    Matrix<MatrixOfNumbersTemplate<T>> resulting_matrix(second_matrix_width, this->height);

    for(unsigned int i = 0; i < this->height; i++){
      MatrixOfNumbersTemplate<T>* row = this->get_row(i);
      
      for(unsigned int j = 0; j < second_matrix_width; j++){
        MatrixOfNumbersTemplate<T>* column = another_matrix.get_column(j);
      
        MatrixOfNumbersTemplate<T> value = 0;
        for(unsigned int n_index = 0; n_index < this->width; n_index++)
          value += row[n_index]*column[n_index];

        resulting_matrix.update_value(i, j, value);
        delete column;
      }  
      delete row;
    }
    
    return resulting_matrix;
  }

  template <typename T> void Matrix<T>::show(){
    for(unsigned int i = 0; i < this->height; i++){
      for(unsigned int j = 0; j < this->width; j++)
        std::cout << this->get_position_value(i, j) << " "; 
      std::cout << "" << std::endl;
    }
  }

  template <typename T> Matrix<T>::~Matrix(){
    this->Matrix::clear_pointers();
  }
  
  template <typename T> void Matrix<T>::transpose(){
    T** transposed_matrix = this->Matrix::generate_matrix_body(this->height, this->width);  

    for(unsigned int i = 0; i < this->height; i++)
      for(unsigned int j = 0; j < this->width; j++)
        transposed_matrix[j][i] = this->Matrix::get_position_value(i, j);
    
    unsigned int tmp = this->height;
    this->height = this->width;
    this->width = tmp;

    this->Matrix::clear_pointers();
    this->matrix = transposed_matrix;
  }

  template <typename T> void Matrix<T>::clear_pointers(){
    for(unsigned int i = 0; i < this->height; i++)
      delete this->matrix[i];
    delete this->matrix;  
  }

  template <typename T> T **Matrix<T>::generate_matrix_body(unsigned int width, unsigned int height){
    T** new_matrix = new T*[height];
    for(unsigned int i = 0; i<height; i++)
      new_matrix[i] = new T[width];

    return new_matrix;
  }
}
