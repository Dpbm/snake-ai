#pragma once

#include <vector>
#include "gene.h"

using std::vector;
using Genes::Gene;

namespace Chromosomes {

  class Chromosome{
    public:
      Chromosome();
      void add_genes(unsigned int size);
      Chromosome(unsigned int size); 
      Chromosome(Gene* genes, unsigned int size);
      Gene* get_genes();
      void mutate(float rate);
      void show();
      unsigned int get_size();
      ~Chromosome();
    
    private:
      Gene* genes = nullptr;
      unsigned int total_genes = 0;
  };
}
