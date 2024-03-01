#pragma once

namespace Matrices {
  class Matrix{
    public:
      Matrix(unsigned int length);
      Matrix(unsigned int width, unsigned int height);
      double** get_matrix();
      void update_value(unsigned int i, unsigned int j, double value);
      double get_position_value(unsigned int i, unsigned int j) const;
      Matrix* operator *(const Matrix& another_matrix);
      unsigned int get_height() const;
      unsigned int get_width() const;
      double* get_row(unsigned int i) const;
      double* get_column(unsigned int j) const;
      void show();
      ~Matrix();
      void map_to_a_single_value(double value);
    
    private:
      unsigned int width, height;
      double** matrix;
      void clear_pointers();
      double** generate_matrix_body(unsigned int width, unsigned int height);
  };

};

