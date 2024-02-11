#pragma once

#include "../genetic/gene.h"

using Genes::Gene;

namespace Matrices {
  template <typename T>
  class Matrix{
    public:
      Matrix(unsigned int length);
      Matrix(unsigned int width, unsigned int height);
      T** get_matrix();
      void update_value(unsigned int i, unsigned int j, double value);
      double get_position_value(unsigned int i, unsigned int j) const;
      Matrix<double>* operator *(const Matrix<Gene>& another_matrix);
      unsigned int get_height() const;
      unsigned int get_width() const;
      double* get_row(unsigned int i) const;
      double* get_column(unsigned int j) const;
      void show();
      ~Matrix();
      void transpose();
      void map_to_a_single_value(double value);
    
    private:
      unsigned int width, height;
      T** matrix;
      void clear_pointers();
      T** generate_matrix_body(unsigned int width, unsigned int height);
  };

};

