#pragma once

#include <iostream>
#include "chromosome.h"

using Chromosomes::Chromosome;

namespace Populations {
  class Population{
    public: 
      Population(unsigned int total_individuals, unsigned int chromosome_size, int total_points);
      Population(Chromosome *chromosomes, unsigned int total_individuals, int total_points);
      unsigned int get_total_individuals();
      unsigned int get_chromosomes_size();
      void reward_all(int* rewards);
      void new_generation(int cutoff);
      Chromosome* get_individuals();
      void show();
      ~Population();
      int get_highest_score();
      
    
    private:
      unsigned int total_individuals = 0;
      int total_points = 0;
      unsigned int chromosome_size = 0;
      Chromosome *individuals = nullptr;
  };
};
