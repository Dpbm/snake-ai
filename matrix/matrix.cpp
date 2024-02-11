#include <iostream>
#include <stdexcept>
#include "matrix.h"
#include "../genetic/gene.h"

using Genes::Gene;

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
  
  template <typename T> void Matrix<T>::map_to_a_single_value(double value){
    for(unsigned int i = 0; i < this->height; i++)
      for(unsigned int j = 0; j < this->width; j++)
        this->update_value(i, j, value);
  }
 
  template<> void Matrix<double>::update_value(unsigned int i, unsigned int j, double value){
    if(i >= this->height || j >= this->width)
      throw std::invalid_argument("i and j must be a value within the bounds of the matrix"); 

    this->matrix[i][j] = value;
  }
  
  template<> void Matrix<Gene>::update_value(unsigned int i, unsigned int j, double value){
    if(i >= this->height || j >= this->width)
      throw std::invalid_argument("i and j must be a value within the bounds of the matrix"); 

    this->matrix[i][j].set_gene_value(value);
  }


  template <> double Matrix<double>::get_position_value(unsigned int i, unsigned int j) const {
    if(i >= this->height || j >= this->width) 
      throw std::invalid_argument("i and j must be a value within the bounds of the matrix");
    return this->matrix[i][j];
  }
  
  template <> double Matrix<Gene>::get_position_value(unsigned int i, unsigned int j) const {
    if(i >= this->height || j >= this->width) 
      throw std::invalid_argument("i and j must be a value within the bounds of the matrix");
    return this->matrix[i][j].get_gene_value();
  }

  template <typename T> unsigned int Matrix<T>::get_height() const{
    return this->height;
  }
  
  template <typename T> unsigned int Matrix<T>::get_width() const{
    return this->width;
  }
  
  template <typename T> double* Matrix<T>::get_row(unsigned int i) const{
    double* row = new double[this->width];
    for(unsigned int j = 0; j < this->width; j++)
      row[j] = this->get_position_value(i, j);
    return row;
  }
  
  template <typename T> double* Matrix<T>::get_column(unsigned int j) const{
    double* column = new double[this->height];
    for(unsigned int i = 0; i < this->height; i++)
      column[i] = this->get_position_value(i, j);
    return column;
  }

  template<> Matrix<double>* Matrix<double>::operator *(const Matrix<Gene>& another_matrix){
    if(this->width != another_matrix.get_height())
      throw std::invalid_argument("The first matrix's width must be equal to the second's height!");
    
    // here's also a better idea to instanciate in the heap
    unsigned int second_matrix_width = another_matrix.get_width();
    Matrix<double>* resulting_matrix = new Matrix<double>(second_matrix_width, this->height);

    for(unsigned int i = 0; i < this->height; i++){
      double* row = this->get_row(i);
      
      for(unsigned int j = 0; j < second_matrix_width; j++){
        double* column = another_matrix.get_column(j);
      
        double value = 0;
        for(unsigned int n_index = 0; n_index < this->width; n_index++)
          value += row[n_index]*column[n_index];

        resulting_matrix->update_value(i, j, value);
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
    this->clear_pointers();
  }
  
  template <> void Matrix<double>::transpose(){
    double** transposed_matrix = this->generate_matrix_body(this->height, this->width);
    for(unsigned int i = 0; i < this->height; i++)
      for(unsigned int j = 0; j < this->width; j++)
        transposed_matrix[j][i] = this->get_position_value(i, j);
    
    unsigned int tmp = this->height;
    this->height = this->width;
    this->width = tmp;

    this->clear_pointers();
    this->matrix = transposed_matrix;
  }
  
  template <> void Matrix<Gene>::transpose(){
    Gene** transposed_matrix = this->generate_matrix_body(this->height, this->width);
    for(unsigned int i = 0; i < this->height; i++)
      for(unsigned int j = 0; j < this->width; j++)
        transposed_matrix[j][i].set_gene_value(this->get_position_value(i, j)); //TODO: check it later (maybe it's not in the heap)
      
    unsigned int tmp = this->height;
    this->height = this->width;
    this->width = tmp;
    
    this->clear_pointers();
    this->matrix = transposed_matrix;
  }

  template <typename T> void Matrix<T>::clear_pointers(){
    delete[] this->matrix;
  }

  template <typename T> T** Matrix<T>::generate_matrix_body(unsigned int width, unsigned int height){
    T** new_matrix = new T*[height];
    for(unsigned int i = 0; i<height; i++)
      new_matrix[i] = new T[width];
    return new_matrix;
  } 

  template class Matrix<double>;
  template class Matrix<Gene>;
}
