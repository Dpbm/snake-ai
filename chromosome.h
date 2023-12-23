#ifndef CHROMOSOME
#define CHROMOSOME

#include <vector>
#include "gene.h"

namespace Chromosomes {

  class Chromosome{
    public:
      Chromosome(unsigned int size); 
      void set_genes(std::vector<Genes::Gene> genes);
      std::vector<Genes::Gene> get_genes();
      std::vector<Genes::Gene> slice(unsigned int start, unsigned int end);
      void crossover(unsigned int start, unsigned int end, std::vector<Genes::Gene> genes_slice);
      void mutate(float rate);
      void show();
    
    private:
      std::vector<Genes::Gene> genes;
      unsigned int total_genes;
      void add_genes(unsigned int size);
  };
}

#endif // !CHROMOSOME
