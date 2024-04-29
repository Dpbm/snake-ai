#pragma once

#include <cstdint>
#include <iostream>
#include <vector>
#include "../matrix/matrix.h"
#include "../machine/machine.h"

using std::vector;
using std::string;
using Matrices::Matrix;
using Machine::NN;

namespace Utils {
  typedef struct vec2{
    int16_t x,y;
  }vec2;

  double random(double start, double end);
  int16_t random_int(uint8_t start, uint8_t end);
  void append_to_file(string filename, string data);
  void create_file(string filename, string data);
  vector<Matrix*> parse_weigths(string filename);
  NN* parse_nn(string filename);
  uint8_t* parse_nn_arch(string line);
  uint8_t* parse_layers_sizes(string line, uint8_t total_layers);
  uint8_t* parse_activations(string line, uint8_t total_layers);
  Matrix* parse_weights_head(string line);
  double* parse_row(string line, uint8_t width);  
  double get_angle(int16_t px, int16_t py, int16_t fx, int16_t fy);
}
