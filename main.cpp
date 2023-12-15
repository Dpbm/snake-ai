#include <iostream>
#include <ostream>
#include <vector>
#include "chromosome.h"
#include "gene.h"

int main(){
  std::cout << "---Simple GA test---" << std::endl;
  

  unsigned int size = 10;
  Chromosomes::Chromosome chromosome = Chromosomes::Chromosome(size);
  std::vector<Genes::Gene> genes = chromosome.get_genes();

  for(unsigned int i = 0; i < size; i++){
    std::cout << genes[i].get_gene_value() << std::endl;
  }

  return 0;
}
