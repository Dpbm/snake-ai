#pragma once

#include <vector>
#include "gene.h"

using std::vector;
using Genes::Gene;

namespace Chromosomes {

  class Chromosome{
    public:
      Chromosome();
      Chromosome(unsigned int size, int points); 
      Chromosome(Gene* genes, unsigned int size, int points);
      Gene* get_genes();
      void mutate(float rate);
      void show();
      void update_points(int factor);
      unsigned int get_size();
      int get_points();
      void add_genes(unsigned int size, int points);
      void reset_genes();
      ~Chromosome();
    
    private:
      Gene* genes = nullptr;
      unsigned int total_genes = 0;
      int points = 0;
      int starting_points = 0;
      void set_genes(Gene* genes, unsigned int size);
  };
}
