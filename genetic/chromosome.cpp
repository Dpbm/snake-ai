#include <cstddef>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include "gene.h"
#include "chromosome.h"

using std::invalid_argument;
using std::size_t;
using std::cout;
using std::endl;

namespace Genetic {
  Chromosome::Chromosome(){}

  Chromosome::Chromosome(uint64_t size){
    this->genes = new Gene[size];
    this->total_genes = size;
  }
 
  Chromosome::Chromosome(Gene* genes, uint64_t size){
    this->genes = genes;
    this->total_genes = size;
  }

  void Chromosome::copy_genes(Gene* genes){
    for(size_t i = 0; i < this->total_genes; i++)
      this->genes[i].set_gene_value(genes[i].get_gene_value());
  }

  Gene* Chromosome::get_genes(){
    return this->genes;
  }
  
  void Chromosome::mutate(float rate){
    for(size_t i = 0; i < this->total_genes; i++)
      this->genes[i].mutate(rate);
  }
 
  void Chromosome::show(){
    for(size_t i = 0; i < this->total_genes; i++)
      cout << this->genes[i].get_gene_value() << " ";
    cout << endl;
  }

  uint64_t Chromosome::get_size(){
    return this->total_genes;
  }
 
  Gene** Chromosome::slice(uint64_t start, uint64_t end){
    if(start > end) 
      throw invalid_argument("invalid start end order!");
    else if(start > this->total_genes || end > this->total_genes)
      throw invalid_argument("start end out of bounds!");

    Gene** genes_slice = new Gene*[end-start];
    for(size_t i = start; i < end; i++)
      genes_slice[i-start] = &this->genes[i];

    //Remember to clean the returning pointer after using that
    return genes_slice;
  }

  Chromosome::~Chromosome(){
    delete[] this->genes;
  }
}

