#include <cstdint>
#include <vector>
#include <iostream>
#include <random>
#include <fstream>
#include "utils.h"
#include "../matrix/matrix.h"
#include "exceptions.h"

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

  // uint16_t get_random_x(uint16_t factor){
  //   uint16_t rand = random_int(LEFT_WALL, WIDTH-factor);
  //   return rand-(rand%factor);
  // }
  // 
  // uint16_t get_random_y(uint16_t factor){
  //   uint16_t rand = random_int(0, HEIGHT-factor);
  //   return rand-(rand%factor);
  // }

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

  vector<Matrix*> parse_weigths_file(string filename){
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
