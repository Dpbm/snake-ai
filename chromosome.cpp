#include <iostream>
#include <vector>
#include <algorithm>
#include "gene.h"
#include "chromosome.h"

namespace Chromosomes {
  std::vector<Genes::Gene> genes;
  unsigned int total_genes;
  int points;

  Chromosome::Chromosome(unsigned int size, int points){
    this->Chromosome::add_genes(size);
    this->total_genes = size;
    this->points = points;
  }

  Chromosome::Chromosome(int points){
    this->points = points;
  }
  
  void Chromosome::set_genes(std::vector<Genes::Gene> genes){
    this->genes = genes;
    this->total_genes = genes.size();
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
 
  std::vector<Genes::Gene> Chromosome::slice(unsigned int start, unsigned int end){
    if(start < 0 || end > this->total_genes || start > end)  
      throw std::invalid_argument("Invalid slice arguments!");
    
    unsigned int size = end-start+1;
    std::vector<Genes::Gene> chromosome_slice(size);
    copy(this->genes.begin()+start, this->genes.begin()+end+1, chromosome_slice.begin());
    return chromosome_slice;
  }

  void Chromosome::crossover(unsigned int start, unsigned int end, std::vector<Genes::Gene> genes_slice){
    if(start < 0 || end > this->total_genes || start > end || end-start+1 != genes_slice.size())
      throw std::invalid_argument("Invalid crossover arguments!");

    std::vector<Genes::Gene> final;
    
    if(start > 0){
      std::vector<Genes::Gene> first = this->slice(0, start-1);
      final.insert(final.end(), first.begin(), first.end());
    }

    final.insert(final.end(), genes_slice.begin(), genes_slice.end());

    if(end < this->total_genes-1){
      std::vector<Genes::Gene> last = this->slice(end+1, this->total_genes-1);
      final.insert(final.end(), last.begin(), last.end());
    }

    this->set_genes(final);
  }

  void Chromosome::show(){
    for(Genes::Gene gene: this->genes)
      std::cout << gene.get_gene_value() << " ";
    std::cout << std::endl;
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

}

