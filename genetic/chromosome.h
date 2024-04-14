#pragma once

#include <cstdint>
#include <vector>
#include "gene.h"

using std::vector;
using Genes::Gene;

namespace Chromosomes {

  class Chromosome{
    public:
      Chromosome(uint64_t size); 
      Chromosome(Gene* genes, uint64_t size);
      Gene* get_genes();
      void mutate(float rate);
      void show();
      uint64_t get_size();
      ~Chromosome();
      void copy_genes(Gene* genes);
      Gene** slice(uint64_t start, uint64_t end);
    
    private:
      Gene* genes = nullptr;
      uint64_t total_genes = 0;
  };
}
