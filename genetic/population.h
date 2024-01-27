#pragma once

#include <iostream>
#include <vector>
#include "chromosome.h"


namespace Populations {
  class Population{
    public: 
      Population(unsigned int total_individuals, unsigned int chromosome_size, int total_points);
      Population();
      void set_individuals(std::vector<Chromosomes::Chromosome*> *chromosomes);
      void reward_individual(Chromosomes::Chromosome* chromosome, int reward);
      void reward_all(std::vector<int>* rewards);
      void new_generation(int cutoff);
      std::vector<Chromosomes::Chromosome*>* get_individuals();
      void show();
      ~Population();
      unsigned int get_total_individuals();
      unsigned int get_chromosomes_size();

    
    private:
      unsigned int total_individuals = 0;
      int total_points = 0;
      unsigned int chromosome_size = 0;
      std::vector<Chromosomes::Chromosome*> *individuals = new std::vector<Chromosomes::Chromosome*>;
      void add_chromosomes();
  };
};
