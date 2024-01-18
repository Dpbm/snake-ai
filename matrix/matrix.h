#ifndef MATRIX
#define MATRIX

namespace Matrices {
  
  class Matrix{

    public:
      Matrix(unsigned int length);
      Matrix(unsigned int input_width, unsigned int input_height);
      void zeros();
      double** get_matrix();
      void update_value(unsigned int i, unsigned int j, double value);
    private:
      unsigned int width, height;
      double** matrix;
  };

};

#endif // !MATRIX 
