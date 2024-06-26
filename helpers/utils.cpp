#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <string>
#include <vector>
#include <iostream>
#include <random>
#include <fstream>
#include "utils.h"
#include "exceptions.h"
#include "../matrix/matrix.h"
#include "../machine/machine.h"

using std::invalid_argument;
using std::pow;
using std::sqrt;
using std::stod;
using std::stoi;
using std::vector;
using std::ofstream;
using std::ifstream;
using std::string;
using std::ios;
using std::random_device;
using std::mt19937;
using std::uniform_real_distribution;
using std::uniform_int_distribution;
using Matrices::Matrix;
using Machine::NN;

namespace Utils {
  double random(double start, double end){
    random_device device;
    mt19937 eng(device());
    uniform_real_distribution<double> distr(start, end);
    return distr(eng);
  }
  
  int64_t random_int(uint64_t start, uint64_t end){
    random_device device;
    mt19937 eng(device());
    uniform_int_distribution<int64_t> distr(start, end);
    int64_t result = distr(eng);
    return result;
  }

  void append_to_file(string filename, string data){
    ofstream file;
    file.open(filename, ios::app);

    if(!file){
      create_file(filename, data);
      return;
    }
    file << data;
    file.close();
  }

  void create_file(string filename, string data){
    ofstream file(filename);

    if(file.is_open()){
      file << data;
      file.close();
    }
  }

  NN* parse_nn(string filename){
    ifstream file;
    file.open(filename, ios::app);
    
    if(!file)
      throw FileNotFound(); 

    NN* nn = new NN;
 
    size_t actual_line = 0;
    uint8_t* layers_amount = nullptr;
    uint8_t total_layers = 0;
    uint8_t* layers_sizes = nullptr;
   
    vector<Matrix*> weights;
    uint8_t weights_counter = 0;
    uint8_t row_i = 0;
    uint8_t row_width = 0;


    for(string line; getline(file, line);){
      switch(actual_line){
        case 0:
          layers_amount = parse_nn_arch(line);
          total_layers = layers_amount[0]+layers_amount[1]+layers_amount[2];
          break;
        
        case 1:
          layers_sizes = parse_layers_sizes(line, total_layers);  
          break;

        case 2:{
          uint8_t* activations = parse_activations(line,total_layers-1);
          for(size_t i = 0; i < total_layers; i++){
            
            nn->add_layer(layers_sizes[i]);
            
            if(i != 0){
              switch (activations[i-1]) {
                case 0:
                  nn->get_layer(i)->relu();
                  break;
                case 1:
                  nn->get_layer(i)->sigmoid();
                  break;
                case 2:
                  nn->get_layer(i)->tanh();
                  break;
                case 3:
                  nn->get_layer(i)->softmax();
                  break;
                default:
                  break;
              }
            }
          }

          delete activations;
          break; 
        }

        default:{
          if(line[0] == 'l'){
            weights.push_back(parse_weights_head(line));
            row_width = weights.at(weights_counter)->get_width();
            row_i = 0;
            weights_counter++;
          
          } else{
            double* row = parse_row(line, row_width);
            for(size_t j = 0; j < row_width; j++)
              weights.at(weights_counter-1)->update_value(row_i, j, row[j]);
            row_i++;
            delete row;
          
          }
          break;
        }

      }

      actual_line++;
    }
    
    nn->load_weights(weights);
    

    delete layers_amount;
    delete layers_sizes;
    file.close();
    return nn;    
  }

  uint8_t* parse_nn_arch(string line){
    uint8_t* sizes = new uint8_t[3]; 
    uint8_t actual_layer = 0;

    if(line.size() <= 0)
      throw invalid_argument("no arch was provided!");

    string value = "";
    for(char a: line){
      if(a == ',' || a == '.'){
        
        if(actual_layer >= 3)
          throw invalid_argument("you must have 3 layers only!");


        sizes[actual_layer] = stoi(value);
        actual_layer ++;
        value = "";
        
        if(a == '.')
          break;

        continue;
      }
      
      value += a;
    }

    if(actual_layer != 3)
      throw invalid_argument("provided arch has less than 3 layers!");

    return sizes;
  }
  
  uint8_t* parse_layers_sizes(string line, uint8_t total_layers){
    uint8_t* sizes = new uint8_t[total_layers]; 
    uint8_t actual_i = 0;

    if(line.size() <= 0)
      throw invalid_argument("Invalid Layers sizes empty line!");

    string value = "";
    for(char a: line){
      if(a == ',' || a == '.'){
        
        if(actual_i >= total_layers)
          throw invalid_argument("Invalid layers amount!");
        
        sizes[actual_i] = stoi(value);
        actual_i ++;
        value = "";
        if(a == '.')
          break;
        continue;
      }
      
      value += a;
    }

    if(actual_i != total_layers)
      throw invalid_argument("Invalid layers amount!");

    return sizes;
  }
  
  uint8_t* parse_activations(string line, uint8_t total_activations){
    uint8_t* activations = new uint8_t[total_activations]; 
    uint8_t actual_i = 0;

    if(line.size() <= 0)
      throw invalid_argument("activations line is empty!");

    string value = "";
    for(char a: line){
      if(a == ',' || a == '.'){

        if(actual_i >= total_activations)
          throw invalid_argument("Invalid amount of activations!");

        if(strcmp(value.c_str(), "relu") == 0)
          activations[actual_i] = 0;
        else if(strcmp(value.c_str(), "sigmoid") == 0)
          activations[actual_i] = 1;
        else if(strcmp(value.c_str(), "tanh") == 0)
          activations[actual_i] = 2;
        else if(strcmp(value.c_str(), "softmax") == 0)
          activations[actual_i] = 3;
        else
          activations[actual_i] = 4;
          
        actual_i ++;
        value = "";
        if(a == '.')
          break;

        continue;
      }
      
      value += a;
    }

    if(actual_i != total_activations)
      throw invalid_argument("Different amount of activations!");

    return activations;
  }
  

  Matrix* parse_weights_head(string line){
    uint8_t values[2];
    uint8_t i = 0;
    
    if(line.size() <= 0)
      throw invalid_argument("no weights head was provided!");

    string value = "";
    for(char a: line){
      if(a == ',' || a == '.'){
        
        if(i >= 2)
          throw invalid_argument("Weights head must have only 2 values!");

        values[i] = stoi(value);
        i++;
        value = "";
        if(a == '.')
          break;

        continue;
      }

      if(a != 'l')
        value += a;
    }
    
    if(i != 2)
      throw invalid_argument("weights head must constist of 2 values!");

    return new Matrix(values[0], values[1]);
  }

  double* parse_row(string line, uint8_t width){  
    double* row = new double[width];
    uint8_t i = 0;
    string weight = "";
      
    
    if(line.size() <= 0)
      throw invalid_argument("Invalid empty weights row!");

    for(char a : line){
      if(a == ',' || a == ';'){

        if(i >= width)
          throw invalid_argument("Invalid row width!");
        

        row[i] = stod(weight);
        i++;
        weight = "";
        
        if(a == ';')
          break;

        continue;
      }

      weight += a;
    }

    if(i != width)
      throw invalid_argument("Invalid row width!");

    return row;
  }

  double distance(int16_t x1, int16_t y1, int16_t x2, int16_t y2){
    return sqrt(pow(x1-x2, 2) + pow(y1-y2, 2));
  }

}
