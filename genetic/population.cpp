#include "chromosome.h"
#include "population.h"
#include <limits>
#include <vector>

using std::vector;
using std::numeric_limits;
using Chromosomes::Chromosome;

namespace Populations {
  unsigned int total_individuals;
  unsigned int chromosome_size;
  vector<Chromosome*> *individuals;
  int total_points;

  Population::Population(unsigned int total_individuals, unsigned int chromosome_size, int total_points){
    this->total_individuals = total_individuals;
    this->total_points = total_points;
    this->chromosome_size = chromosome_size;
    this->Population::add_chromosomes();
  }

  Population::Population(){}

  unsigned int Population::get_total_individuals(){
    return this->total_individuals;
  }
  
  unsigned int Population::get_chromosomes_size(){
    return this->chromosome_size;
  }

  void Population::set_individuals(vector<Chromosome*> *chromosomes){
    if(chromosomes->size() == 0)
      throw std::invalid_argument("You need to add at least 1 individual!");

    this->individuals = chromosomes;
    this->total_individuals = chromosomes->size();
    this->chromosome_size = chromosomes->at(0)->get_size();
    this->total_points = chromosomes->at(0)->get_points();
  }

  void Population::add_chromosomes(){
    for(unsigned int i = 0; i < this->total_individuals; i++)
      this->individuals->push_back(new Chromosome(this->chromosome_size, this->total_points));
  }
  
  void Population::reward_individual(Chromosome* chromosome, int reward){
    chromosome->update_points(reward); 
  }

  void Population::reward_all(vector<int>* rewards){
    if(rewards->size() != this->total_individuals)
      throw std::invalid_argument("Invalid rewards size, it must be equals to the total of individuals!");

    for(unsigned int i = 0; i < this->total_individuals; i++){
      Chromosome* chromosome = this->individuals->at(i);
      chromosome->update_points(rewards->at(i));
    }
  }

  void Population::new_generation(int cutoff){
    for(int i = this->total_individuals-1; i >= 0; i--){
      Chromosome* chromosome = this->individuals->at(i);
      if(chromosome->get_points() < cutoff){
        this->individuals->erase(this->individuals->begin()+i);
        this->individuals->insert(this->individuals->begin()+i, new Chromosome(this->chromosome_size, this->total_points));
        delete chromosome;
      }
    } 
  }
  
  vector<Chromosome*>* Population::get_individuals(){
    return this->individuals;
  }

  void Population::show(){
    for(Chromosome* chromosome : (*this->individuals))
      chromosome->show();
  }

  Population::~Population(){
    for(Chromosome *chromosome: (*this->individuals))
      delete chromosome;
    delete this->individuals;
  }

  int Population::get_highest_score(){
    int highest_score = numeric_limits<int>::min();
    
    for(Chromosome *chromosome : (*this->individuals)){
      int chromosome_points = chromosome->get_points();
      if(chromosome_points > highest_score)
        highest_score = chromosome_points;
    }
    return highest_score;
  }
}
