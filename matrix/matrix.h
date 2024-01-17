#ifndef MATRIX
#define MATRIX

namespace Matrices {
  
  class Matrix{

    public:
      Matrix(unsigned int length);
      Matrix(unsigned int input_width, unsigned int input_height);
      void zeros();
      double** get_matrix();
    private:
      unsigned int width, height;
      double** matrix;
  };

};

#endif // !MATRIX 
