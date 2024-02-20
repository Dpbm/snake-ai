#include <iostream>
#include <random>
#include <fstream>
#include <SDL2/SDL_timer.h>
#include "utils.h"
#include "constants.h"
#include "../genetic/gene.h"
#include "../matrix/matrix.h"

using std::vector;
using std::ofstream;
using std::string;
using std::ios;
using Genes::Gene;
using Matrices::Matrix;

namespace Utils {
  double random(int start, int end){
    std::random_device device;
    std::mt19937 eng(device());
    std::uniform_real_distribution<> distr(start, end);
    
    return distr(eng);
  }
  
  unsigned int random_int(int start, int end){
    std::random_device device;
    std::mt19937 eng(device());
    std::uniform_int_distribution<> distr(start, end);
    
    return distr(eng);
  }

  unsigned int get_random_pos(unsigned int max_range, unsigned int factor){
    unsigned int rand = Utils::random_int(0, max_range);
    return rand-(rand%factor);
  }

  void append_to_file(string filename, string data){
    ofstream file;
    file.open(filename, ios::app);

    if(!file){
      Utils::create_file(filename, data);
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

  bool passed_debounce_time(int last_tick){
    return SDL_GetTicks() - last_tick >= DEBOUNCE_TIME;
  }

  vector<Gene*>* weights_to_genes_vector(Matrix<Gene>* weights){
    vector<Gene*> *genes = new vector<Gene*>;
    Gene** weights_matrix = weights->get_matrix();
    for(unsigned int i = 0; i < weights->get_height(); i++)
      for(unsigned int j = 0; j < weights->get_width(); j++)
        genes->push_back(&weights_matrix[i][j]);
    return genes;
  } 

  template <typename T> 
  void concat_vectors(vector<T>* vector_a, vector<T>* vector_b, vector<T>* target_vector){
    target_vector->insert(target_vector->end(), vector_a->begin(), vector_a->end());
    target_vector->insert(target_vector->end(), vector_b->begin(), vector_b->end());
  }

  template void concat_vectors<Gene*>(vector<Gene*>* vector_a, vector<Gene*>* vector_b, vector<Gene*>* target_vector);
}
