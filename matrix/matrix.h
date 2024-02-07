#pragma once

#include <iostream>
#include <type_traits>
#include <sched.h>
#include "../genetic/gene.h"

using std::enable_if;
using std::is_integral;
using std::is_floating_point;
using std::is_same;

namespace Matrices {
 
  template <typename T,
            typename enable_if<is_floating_point<T>::value || is_integral<T>::value>::type* = nullptr> 
    using MatrixOfNumbersTemplate = T;

  template <typename T>
  class Matrix{
    public:
      Matrix(unsigned int length);
      Matrix(unsigned int width, unsigned int height);
      void random(int start, int end);
      T** get_matrix();
      void update_value(unsigned int i, unsigned int j, T value);
      T get_position_value(unsigned int i, unsigned int j) const;
      Matrix<MatrixOfNumbersTemplate<T>> operator *(MatrixOfNumbersTemplate<T> scalar);
      Matrix<T> copy();
      void operator=(const Matrix<T>& another_matrix);
      Matrix<MatrixOfNumbersTemplate<T>> operator *(const Matrix<MatrixOfNumbersTemplate<T>>& another_matrix);
      unsigned int get_height() const;
      unsigned int get_width() const;
      T* get_row(unsigned int i) const;
      T* get_column(unsigned int j) const;
      void show();
      ~Matrix();
      void transpose();
      void map_to_a_single_value(T value);
    
    private:
      unsigned int width, height;
      T** matrix;
      void clear_pointers();
      T** generate_matrix_body(unsigned int width, unsigned int height);
  };

};

