#pragma once

#include <cstdint>
#include <iostream>
#include "../matrix/matrix.h"
#include "../machine/machine.h"

using std::string;
using Matrices::Matrix;
using Machine::NN;

namespace Utils {
  typedef struct vec2{
    int16_t x,y;
  }vec2;

  double random(double start, double end);
  int64_t random_int(uint64_t start, uint64_t end);
 
  void create_file(string filename, string data);
  void append_to_file(string filename, string data);
  
  uint8_t* parse_nn_arch(string line);
  double distance(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
  Matrix* parse_weights_head(string line);
  uint8_t* parse_layers_sizes(string line, uint8_t total_layers);
  uint8_t* parse_activations(string line, uint8_t total_activations);
  double* parse_row(string line, uint8_t width);
  NN* parse_nn(string filename);
}
