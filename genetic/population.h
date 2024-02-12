#pragma once

#include <iostream>
#include <vector>
#include "chromosome.h"

using std::vector;
using Chromosomes::Chromosome;

namespace Populations {
  class Population{
    public: 
      Population(unsigned int total_individuals, unsigned int chromosome_size, int total_points);
      Population();
      void set_individuals(vector<Chromosome*> *chromosomes);
      void reward_individual(Chromosome* chromosome, int reward);
      void reward_all(vector<int>* rewards);
      void new_generation(int cutoff);
      vector<Chromosome*>* get_individuals();
      void show();
      ~Population();
      unsigned int get_total_individuals();
      unsigned int get_chromosomes_size();
      int get_highest_score();

    
    private:
      unsigned int total_individuals = 0;
      int total_points = 0;
      unsigned int chromosome_size = 0;
      vector<Chromosome*> *individuals = new vector<Chromosome*>;
      void add_chromosomes();
  };
};
