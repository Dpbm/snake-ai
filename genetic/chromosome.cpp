#include <iostream>
#include <vector>
#include "gene.h"
#include "chromosome.h"

using std::vector;
using Genes::Gene;

namespace Chromosomes {
  vector<Gene*> *genes;
  unsigned int total_genes;
  int points;

  Chromosome::Chromosome(unsigned int size, int points){
    this->add_genes(size);
    this->total_genes = size;
    this->points = points;
  }
 
  Chromosome::Chromosome(vector<Gene*>* genes, int points){
    this->genes = genes;
    this->total_genes = genes->size();
    this->points = points;
  }

  vector<Gene*>* Chromosome::get_genes(){
    return this->genes;
  }

  void Chromosome::add_genes(unsigned int size){
    for(unsigned int i = 0; i < size; i++)
      this->genes->push_back(new Gene);
  }
  
  void Chromosome::mutate(float rate){
    for(Gene *gene: (*this->genes))
      gene->mutate(rate);
  }
 
  vector<Gene*> *Chromosome::slice(unsigned int start, unsigned int end){
    if(this->total_genes == 0 || end > this->total_genes-1 || start > end)  
      throw std::invalid_argument("Invalid slice arguments!");
    
    vector<Gene*> *chromosome_slice = new vector<Gene*>;
    
    for(unsigned int i = start; i <= end; i++)
      chromosome_slice->push_back(this->genes->at(i)->copy());    
    
    return chromosome_slice;
  }

  void Chromosome::crossover(unsigned int start, unsigned int end, vector<Gene*> *genes_slice){
    if(end-start+1 != genes_slice->size())
      throw std::invalid_argument("Invalid crossover arguments!");

    vector<Gene*>* final = new vector<Gene*>;
    
    if(start > 0){
      vector<Gene*> *first = this->slice(0, start-1);
      final->insert(final->end(), first->begin(), first->end());
      delete first;
    }
    
    // clear the old genes in the start->end positions 
    for(unsigned int i = start; i <= end; i++)
      delete this->genes->at(i);
    
    final->insert(final->end(), genes_slice->begin(), genes_slice->end());

    if(end < this->total_genes-1){
      vector<Gene*> *last = this->slice(end+1, this->total_genes-1);
      final->insert(final->end(), last->begin(), last->end());
      delete last;
    }
    
    delete this->genes;
    this->set_genes(final);
  }

  void Chromosome::set_genes(vector<Gene*>* genes){
    this->genes = genes;
    this->total_genes = genes->size();
  }

  void Chromosome::show(){
    for(Gene* gene: (*this->genes))
      std::cout << gene->get_gene_value() << " ";
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
  
  Chromosome::~Chromosome(){
    for(Gene* gene : (*this->genes))
      delete gene;
    this->clear_gene_vector_pointer();
  }
  
  void Chromosome::clear_gene_vector_pointer(){
    delete this->genes;
  }

}

