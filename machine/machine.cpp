#include <iostream>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <vector>
#include "layer.h"
#include "weights.h"
#include "machine.h"
#include "../helpers/utils.h"

using std::cout;
using std::endl;
using std::stringstream;
using std::vector;
using std::string;
using std::invalid_argument;
using Utils::append_to_file;

namespace Machine {
  void NN::add_layer(unsigned int size){
    this->layers.push_back(new Layer(size, this->total_layers==0));
    this->total_layers++;
    this->add_weight();
  }
   
  void NN::add_layer(Layer* layer){
    this->layers.push_back(layer);
    this->total_layers++;
    this->add_weight();
  } 

   
  void NN::add_weight(){
    if(this->total_layers <= 1)
      return;
   
    unsigned int first_layer_size = this->layers.at(this->total_layers-2)->get_size(); 
    unsigned int second_layer_size = this->layers.at(this->total_layers-1)->get_size();
    this->weights.push_back(new Weights(second_layer_size, first_layer_size));
    this->total_weights++;
  }

   
  vector<Layer*> NN::get_layers(){
    return this->layers;
  }

   
  void NN::save_weights(string filename){
    char* weights_path = getenv("WPATH");

    stringstream path_construct;

    if(weights_path != nullptr)
       path_construct << weights_path;
    
    path_construct << filename;


    string path = path_construct.str();
    cout << "Path: " << path << endl;

    this->save_arch(path);
    for(Weights* weight: this->weights)
      weight->save_weights(path);
  }


  void NN::save_arch(string path){
    stringstream arch;
 
    if(this->total_layers <= 1)
      arch << this->total_layers << "," << 0 << "," << 0 << "." << "\n";
    else
      arch << 1 << "," << this->total_layers-2 << "," << 1 << "." << "\n";   
    

    for(size_t i = 0; i < this->total_layers; i++){
      arch << this->get_layer(i)->get_size();

      if(i == this->total_layers-1)
        arch << "." << "\n";
      else 
        arch << ",";
    }    
    


    for(size_t i = 0; i < this->total_layers; i++){
      if(this->layers.at(i)->is_input())
        continue;
     
      arch << this->layers.at(i)->get_activation_name();
      if(i == this->total_layers-1)
        arch << "." << "\n";
      else
        arch << ",";
    }
  
    append_to_file(path, arch.str());
  }
   
  Layer* NN::get_layer(unsigned int i){
    if(this->total_layers == 0 || i > this->total_layers-1)
      throw invalid_argument("invalid layer position");

    return this->layers.at(i);
  }
  
   
  Weights* NN::get_weight(unsigned int i){
    if(this->total_weights == 0 || i > this->total_weights-1)
      throw invalid_argument("invalid weights position");
    return this->weights.at(i);
  }
  
   
  vector<Weights*> NN::get_weights(){
    return this->weights;
  }
  

   
  unsigned int NN::get_total_layers(){
    return this->total_layers;
  }
  
   
  unsigned int NN::get_total_weights(){
    return this->total_weights;
  } 

   
  NN::~NN(){
    for(Layer *layer: this->layers)
      delete layer;
    for(Weights *weight: this->weights)
      delete weight;
  }

   
  void NN::feedforward(){
    for(unsigned int layer = 0; layer < this->total_layers-1; layer++){
      Layer* actual_layer = this->get_layer(layer);
      Layer* next_layer = this->get_layer(layer+1);

      Matrix* layer_values = actual_layer->get_values();
      Matrix* layer_weights = this->get_weight(layer)->get_weights();

      Matrix* dot_product_result = (*layer_values) * (*layer_weights);
      next_layer->set_values(dot_product_result);
      next_layer->activate_neurons();
    }
  }


  void NN::load_weights(vector<Matrix*> new_weights){
    for(size_t i = 0; i < this->total_weights; i++){
      this->weights[i]->load_weights(new_weights.at(i));
    }
  }

  Layer* NN::get_output_layer(){
    return this->layers.at(this->total_layers-1);
  }
  
  Layer* NN::get_input_layer(){
    return this->layers.at(0);
  }
}
