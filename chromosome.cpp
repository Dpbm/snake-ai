#include <iostream>
#include <vector>
#include "gene.h"
#include "chromosome.h"

namespace Chromosomes {
  std::vector<Genes::Gene> genes;

  Chromosome::Chromosome(unsigned int size){
    this->Chromosome::add_genes(size);
  }
  
  void Chromosome::set_genes(std::vector<Genes::Gene> genes){
    this->genes = genes;
  }

  std::vector<Genes::Gene> Chromosome::get_genes(){
    return this->genes;
  }

  void Chromosome::add_genes(unsigned int size){
    for(unsigned int i = 0; i < size; i++)
      this->genes.push_back(Genes::Gene());
  }
  
  void Chromosome::mutate(float rate){
    for(Genes::Gene& gene: this->genes)
      gene.mutate(rate);
  }
  
  void Chromosome::show(){
    for(Genes::Gene gene: this->genes)
      std::cout << gene.get_gene_value() << " ";
    std::cout << std::endl;
  }

}

