#pragma once

#include <vector>
#include "gene.h"

using std::vector;
using Genes::Gene;

namespace Chromosomes {

  class Chromosome{
    public:
      Chromosome(unsigned int size, int points); 
      Chromosome(Gene* genes, unsigned int size, int points);
      Gene* get_genes();
      Gene* slice(unsigned int start, unsigned int end);
      void crossover(unsigned int start, unsigned int end, Gene *genes_slice);
      void mutate(float rate);
      void show();
      void update_points(int factor);
      unsigned int get_size();
      int get_points();
      ~Chromosome();
    
    private:
      Gene* genes = nullptr;
      unsigned int total_genes = 0;
      int points = 0;
      void set_genes(Gene* genes, unsigned int size);
  };
}
