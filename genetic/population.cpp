#include <limits>
#include "population.h"
#include "chromosome.h"

using std::numeric_limits;
using Chromosomes::Chromosome;

namespace Populations {
  unsigned int total_individuals;
  unsigned int chromosome_size;
  Chromosome *individuals;
  int total_points;

  Population::Population(unsigned int total_individuals, unsigned int chromosome_size, int total_points){
    this->total_individuals = total_individuals;
    this->total_points = total_points;
    this->chromosome_size = chromosome_size;
    this->individuals = new Chromosome[total_individuals];
    for(unsigned int i = 0; i < total_individuals; i++)
      this->individuals[i].add_genes(this->chromosome_size, this->total_points);
}
  
  Population::Population(Chromosome *chromosomes, unsigned int total_individuals, int total_points){
    this->individuals = chromosomes;
    this->total_individuals = total_individuals;
    this->chromosome_size = chromosomes[0].get_size();
    this->total_points = total_individuals;
  }

  unsigned int Population::get_total_individuals(){
    return this->total_individuals;
  }
  
  unsigned int Population::get_chromosomes_size(){
    return this->chromosome_size;
  }

  void Population::reward_all(int* rewards){
    for(unsigned int i = 0; i < this->total_individuals; i++)
      this->individuals[i].update_points(rewards[i]);
  }

  void Population::new_generation(int cutoff){
    for(unsigned int i = 0; i < this->total_individuals; i++){
      if(this->individuals[i].get_points() < cutoff)
        this->individuals[i].reset_genes();
    }
  }

  Chromosome* Population::get_individuals(){
    return this->individuals;
  }

  void Population::show(){
    for(unsigned int i = 0; i < this->total_individuals; i++)
      this->individuals[i].show();
  }

  Population::~Population(){
    delete[] this->individuals;
  }

  int Population::get_highest_score(){
    int highest_score = numeric_limits<int>::min();
    
    for(unsigned int i = 0; i < this->total_individuals; i++){
      int chromosome_points = this->individuals[i].get_points();
      if(chromosome_points > highest_score)
        highest_score = chromosome_points;
    }
    return highest_score;
  }
}
