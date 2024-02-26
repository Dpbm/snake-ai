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

