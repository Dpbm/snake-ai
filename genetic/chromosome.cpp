#include <iostream>
#include <stdexcept>
#include "gene.h"
#include "chromosome.h"

using std::cout;
using std::endl;
using std::invalid_argument;
using Genes::Gene;

namespace Chromosomes {
  Gene* genes;
  unsigned int total_genes;
  int points, starting_points;

  Chromosome::Chromosome(){}

  void Chromosome::add_genes(unsigned int size, int points){
    this->genes = new Gene[size];
    this->total_genes = size;
    this->points = points;
    this->starting_points = points;
  }
  
  void Chromosome::reset_genes(){
    if(this->genes != nullptr)
      delete[] this->genes;
    this->genes = new Gene[this->total_genes];
    this->points = this->starting_points; 
  }

  Chromosome::Chromosome(unsigned int size, int points){
    this->genes = new Gene[size];
    this->total_genes = size;
    this->points = points;
  }
 
  Chromosome::Chromosome(Gene* genes, unsigned int size, int points){
    this->genes = genes;
    this->total_genes = size;
    this->points = points;
  }

  Gene* Chromosome::get_genes(){
    return this->genes;
  }
  
  void Chromosome::mutate(float rate){
    for(unsigned int i = 0; i < this->total_genes; i++)
      this->genes[i].mutate(rate);
  }
 
  Gene* Chromosome::slice(unsigned int start, unsigned int end){
    if(this->total_genes == 0 || end > this->total_genes-1 || start > end)  
      throw invalid_argument("Invalid slice arguments!");
    
    Gene *chromosome_slice = new Gene[end-start+1];
    
    for(unsigned int i = start; i <= end; i++){
      Gene gene;
      gene.set_gene_value(this->genes[i].get_gene_value());
      chromosome_slice[i-start] = gene;   
    }
    
    return chromosome_slice;
  }

  void Chromosome::crossover(unsigned int start, unsigned int end, Gene* genes_slice){
    Gene* new_genes = new Gene[this->total_genes];

    for(unsigned int i = 0; i < this->total_genes; i++){
      if(i < start || i > end)
        new_genes[i] = this->genes[i];
      else
        new_genes[i] = genes_slice[i-start];
      
    } 

    delete[] this->genes;
    this->genes = new_genes;
  }

  void Chromosome::set_genes(Gene* genes, unsigned int size){
    this->genes = genes;
    this->total_genes = size;
  }

  void Chromosome::show(){
    for(unsigned int i = 0; i < this->total_genes; i++)
      cout << this->genes[i].get_gene_value() << " ";
    cout << endl;
  }

  void Chromosome::update_points(int factor){
    this->points += factor;
  }

  unsigned int Chromosome::get_size(){
    return this->total_genes;
  }
  
  int Chromosome::get_points(){
    return this->points;
  }
  
  Chromosome::~Chromosome(){
    delete[] this->genes;
  }
}

