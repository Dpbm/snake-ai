#pragma once

#include <iostream>
#include <type_traits>
#include <sched.h>
#include "../genetic/gene.h"

using std::enable_if;
using std::is_integral_v;
using std::is_floating_point_v;
using std::is_same;
using Genes::Gene;

namespace Matrices {
 
  template <typename T, typename enable_if<is_floating_point_v<T> || is_integral_v<T> || is_same<T, Gene>::value>::type* = nullptr> 
  using MatrixTemplate = T;

  template <MatrixTemplate>
  class Matrix{
    public:
      Matrix(unsigned int length);
      Matrix(unsigned int width, unsigned int height);
      void zeros();
      void ones();
      void random(int start, int end);
      T** get_matrix();
      void update_value(unsigned int i, unsigned int j, T value);
      double get_position_value(unsigned int i, unsigned int j)const;
      Matrix operator *(T scalar);
      Matrix copy();
      void operator=(const Matrix& another_matrix);
      Matrix operator *(const Matrix& another_matrix);
      unsigned int get_height() const;
      unsigned int get_width() const;
      double* get_row(unsigned int i) const;
      double* get_column(unsigned int j) const;
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

