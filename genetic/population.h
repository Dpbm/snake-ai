#pragma once

#include <iostream>
#include <vector>
#include "chromosome.h"


namespace Populations {
  class Population{
    public:
      Population(unsigned int total_individuals, unsigned int chromosome_size, int total_points);
      void set_individuals(std::vector<Chromosomes::Chromosome*> *chromosomes);
      void reward_individual(Chromosomes::Chromosome* chromosome, int reward);
      void reward_all(std::vector<int>* rewards);
      void new_generation(int cutoff);
      std::vector<Chromosomes::Chromosome*>* get_individuals();
      void show();
      ~Population();
    
    private:
      unsigned int total_individuals;
      int total_points;
      unsigned int chromosome_size;
      std::vector<Chromosomes::Chromosome*> *individuals = new std::vector<Chromosomes::Chromosome*>;
      void add_missing_individuals();
      void add_chromosomes();
  };
};
