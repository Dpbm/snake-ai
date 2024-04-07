#include <cstdint>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <random>
#include <fstream>
#include "utils.h"
#include "exceptions.h"
#include "../matrix/matrix.h"
#include "../machine/machine.h"

using std::to_string;
using std::stoi;
using std::stod;
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
  
  int16_t random_int(uint8_t start, uint8_t end){
    random_device device;
    mt19937 eng(device());
    uniform_int_distribution<int16_t> distr(start, end);
    int16_t result = distr(eng);
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
          uint8_t* activations = parse_activations(line,total_layers);
          
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
          break; 
        }

        default:
          break;

      }

      std::cout << line << std::endl;

      actual_line++;
    }

    return nn;    
  }

  uint8_t* parse_nn_arch(string line){
    uint8_t* sizes = new uint8_t[3]; 
    uint8_t actual_layer = 0;

    string value = "";
    for(char a: line){
      if(a == ','){
        
        sizes[actual_layer] = stoi(value);
        actual_layer ++;
        value = "";
        continue;
      }
      
      value += a;
    }

    return sizes;
  }
  
  uint8_t* parse_layers_sizes(string line, uint8_t total_layers){
    uint8_t* sizes = new uint8_t[total_layers]; 
    uint8_t actual_i = 0;

    string value = "";
    for(char a: line){
      if(a == ','){
        
        sizes[actual_i] = stoi(value);
        actual_i ++;
        value = "";
        continue;
      }
      
      value += a;
    }

    return sizes;
  }
  
  uint8_t* parse_activations(string line, uint8_t total_layers){
    uint8_t* activations = new uint8_t[total_layers]; 
    uint8_t actual_i = 0;

    string value = "";
    for(char a: line){
      if(a == ','){
        

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
        continue;
      }
      
      value += a;
    }

    return activations;
  }
  


  vector<Matrix*> parse_weigths(string filename){
    ifstream file;
    file.open(filename, ios::app);
    
    if(!file)
      throw FileNotFound(); 

    vector<Matrix*> matrices;

    uint8_t w,h; 
    string w_str = "";
    string h_str = "";

    uint16_t i = 0;
    uint8_t last_matrix = 0;
    
    for(string line; getline(file, line);){
      std::cout << line << std::endl;

      bool get_w = false;
      bool get_h = false;
      
      string weight = "";
      bool getting_weight = false;
      uint16_t j = 0;

      for(char a : line){
        if(a == 'w'){
          get_w = true;
          continue;
        }else if(a == 'h'){
          get_h = true;
          continue;
        }else if(a == '-' || (a >= '0' and a <= '9')){
          getting_weight = true;
        }
        
        if((get_w || get_h) && a == ';'){
          get_w = false;
          get_h = false;
          continue;
        }else if(getting_weight && a == ','){
          getting_weight = false;
          matrices.at(last_matrix)->update_value(i, j, stod(weight));
          weight = "";
          j++;
        }else if(get_w){
          w_str += a;
        }else if(get_h){
          h_str += a;
        }else if(getting_weight){
          weight += a;    
        }
      }


      if(!weight.empty())
        matrices.at(last_matrix)->update_value(i, j, stod(weight));

      if(!w_str.empty() && !h_str.empty()){
        if(matrices.size() > 0)
          last_matrix++;
        
        uint8_t w = stoi(w_str);
        uint8_t h = stoi(h_str);
        matrices.push_back(new Matrix(w,h));
        w_str = "";
        h_str = "";
        i = 0;
      }else{
        i++;
      }
    }
    return matrices;
  }
}
