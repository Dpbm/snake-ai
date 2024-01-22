#pragma once

namespace Matrices {
  
  class Matrix{

    public:
      Matrix(unsigned int length);
      Matrix(unsigned int width, unsigned int height);
      void zeros();
      double** get_matrix();
      void update_value(unsigned int i, unsigned int j, double value);
      double get_position_value(unsigned int i, unsigned int j);
      Matrices::Matrix operator *(int scalar);
      Matrices::Matrix copy();
    private:
      unsigned int width, height;
      double** matrix;
  };

};

