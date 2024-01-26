#include "chromosome.h"
#include "population.h"
#include <vector>

namespace Populations {
  unsigned int total_individuals;
  unsigned int chromosome_size;
  std::vector<Chromosomes::Chromosome*> *individuals;
  int total_points;

  Population::Population(unsigned int total_individuals, unsigned int chromosome_size, int total_points){
    this->total_individuals = total_individuals;
    this->total_points = total_points;
    this->chromosome_size = chromosome_size;
    this->Population::add_chromosomes();
  }

  void Population::set_individuals(std::vector<Chromosomes::Chromosome*> *chromosomes){
    if(chromosomes->size() == 0)
      throw std::invalid_argument("You need to add at least 1 individual!");

    this->individuals = chromosomes;
    this->chromosome_size = chromosomes->at(0)->get_size();
    this->total_points = chromosomes->at(0)->get_points();
  }

  void Population::add_chromosomes(){
    for(unsigned int i = 0; i < this->total_individuals; i++)
      this->individuals->push_back(new Chromosomes::Chromosome(this->chromosome_size, this->total_points));
  }
  
  void Population::reward_individual(Chromosomes::Chromosome* chromosome, int reward){
    chromosome->update_points(reward); 
  }

  void Population::reward_all(std::vector<int>* rewards){
    if(rewards->size() != this->total_individuals)
      throw std::invalid_argument("Invalid rewards size, it must be equals to the total of individuals!");

    for(unsigned int i = 0; i < this->total_individuals; i++){
      Chromosomes::Chromosome* chromosome = this->individuals->at(i);
      chromosome->update_points(rewards->at(i));
    }
  }

  void Population::new_generation(int cutoff){
    for(unsigned int i = 0; i < this->total_individuals; i++){
      Chromosomes::Chromosome *chromosome = this->individuals->at(i);
      if(chromosome->get_points() <= cutoff){
        this->individuals->erase(this->individuals->begin()+i);
        delete chromosome;
      }
    }  
    
    this->Population::add_missing_individuals();
  }
  
  void Population::add_missing_individuals(){
    unsigned int total_missing_individuals = this->total_individuals - this->individuals->size();
    if(total_missing_individuals == 0)
      return;
  
    for(unsigned int i = 0; i < total_missing_individuals; i++)
      this->individuals->push_back(new Chromosomes::Chromosome(this->chromosome_size, this->total_points));
  }

  std::vector<Chromosomes::Chromosome*>* Population::get_individuals(){
    return this->individuals;
  }

  void Population::show(){
    for(Chromosomes::Chromosome* chromosome : (*this->individuals))
      chromosome->show();
  }

  Population::~Population(){
    for(Chromosomes::Chromosome *chromosome: (*this->individuals))
      delete chromosome;
    delete this->individuals;
  }
}
