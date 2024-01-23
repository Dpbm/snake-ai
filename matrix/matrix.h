#pragma once

namespace Matrices {
  
  class Matrix{

    public:
      Matrix(unsigned int length);
      Matrix(unsigned int width, unsigned int height);
      void zeros();
      double** get_matrix();
      void update_value(unsigned int i, unsigned int j, double value);
      double get_position_value(unsigned int i, unsigned int j)const;
      Matrices::Matrix operator *(int scalar);
      Matrices::Matrix copy();
      void operator=(const Matrices::Matrix& another_matrix);
      Matrices::Matrix operator *(const Matrices::Matrix& another_matrix);
      unsigned int get_height() const;
      unsigned int get_width() const;
      double* get_row(unsigned int i) const;
      double* get_column(unsigned int j) const;
      void show();
      ~Matrix();
    private:
      unsigned int width, height;
      double** matrix;
  };

};

