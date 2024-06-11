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
  int64_t random_int(uint64_t start, uint64_t end);
  void append_to_file(string filename, string data);
  void create_file(string filename, string data);
  vector<Matrix*> parse_weigths(string filename);
  NN* parse_nn(string filename);
  uint8_t* parse_layers_sizes(string line, uint8_t total_layers);
  uint8_t* parse_activations(string line, uint8_t total_layers);
  Matrix* parse_weights_head(string line);
  double* parse_row(string line, uint8_t width);

  //tested
  uint8_t* parse_nn_arch(string line);
  double distance(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
}
