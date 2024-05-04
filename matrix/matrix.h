#pragma once

#include <cstdint>

namespace Matrices {
  class Matrix{
    public:
      Matrix(uint16_t length);
      Matrix(uint16_t width, uint16_t height);
      double** get_matrix();
      void update_value(uint16_t i, uint16_t j, double value);
      double get_position_value(uint16_t i, uint16_t j) const;
      Matrix* operator *(const Matrix& another_matrix);
      uint16_t get_height() const;
      uint16_t get_width() const;
      double* get_row(uint16_t i) const;
      double* get_column(uint16_t j) const;
      void show();
      ~Matrix();
      void map_to_a_single_value(double value);
    
    private:
      uint16_t width, height;
      double** matrix;
      double** generate_matrix_body();
  };

};

