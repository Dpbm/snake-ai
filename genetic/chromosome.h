#pragma once

#include <vector>
#include "gene.h"

using std::vector;
using Genes::Gene;

namespace Chromosomes {

  class Chromosome{
    public:
      Chromosome(unsigned int size, int points); 
      Chromosome(vector<Gene*>* genes, int points);
      vector<Gene*>* get_genes();
      vector<Gene*>* slice(unsigned int start, unsigned int end);
      void crossover(unsigned int start, unsigned int end, vector<Gene*> *genes_slice);
      void mutate(float rate);
      void show();
      void update_points(int factor);
      unsigned int get_size();
      int get_points();
      ~Chromosome();
    
    private:
      vector<Gene*> *genes = new vector<Gene*>;
      unsigned int total_genes = 0;
      int points = 0;
      void add_genes(unsigned int size);
      void set_genes(vector<Gene*>* genes);
  };
}
