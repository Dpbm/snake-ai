#pragma once

#include <iostream>
#include <vector>
#include "chromosome.h"


namespace Populations {
  class Population{
    public:
      Population(unsigned int total_individuals, unsigned int chromosome_size, unsigned int points);
      void set_individuals(std::vector<Chromosomes::Chromosome> chromosomes);
      void reward_individual(Chromosomes::Chromosome chromosome, int reward);
      void reward_all(std::vector<int> rewards);
      void new_generation(unsigned int top);
      std::vector<Chromosomes::Chromosome> get_individuals();
      void show();
    
    private:
      unsigned int total_individuals;
      unsigned int total_points;
      unsigned int chromosome_size;
      std::vector<Chromosomes::Chromosome> individuals;
      void add_chromosomes();
      void add_chromosomes(unsigned int total);
  };
};
