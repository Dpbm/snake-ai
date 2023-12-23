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
      void mutate(float rate);
      void show();
    
    private:
      std::vector<Genes::Gene> genes;
      void add_genes(unsigned int size);
  };
}

#endif // !CHROMOSOME
