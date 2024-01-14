#include "matrix.h"

namespace Matrices{
  double** matrix;
  

  Matrix::Matrix(int length){
    this->matrix = new double*[length];
    for(int i = 0; i< length; i++){
      this->matrix[i] = new double[length];
    }
  }
  

}
