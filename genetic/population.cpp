#include "chromosome.h"
#include "population.h"

namespace Populations {
  unsigned int total_individuals;
  std::vector<Chromosomes::Chromosome> individuals;
  unsigned int total_points;
  unsigned int chromosome_size;

  Population::Population(
    unsigned int total_individuals, 
    unsigned int chromosome_size,
    unsigned int points
  ){
    this->total_individuals = total_individuals;
    this->total_points = points;
    this->chromosome_size = chromosome_size;
    this->Population::add_chromosomes();
  }

  void Population::set_individuals(std::vector<Chromosomes::Chromosome> chromosomes){
    if(chromosomes.size())
      throw std::invalid_argument("You need to add at least 1 individual!");

    this->individuals = chromosomes;
    this->chromosome_size = chromosomes[0].get_size();
    this->total_points = chromosomes[0].get_points();
  }

  void Population::add_chromosomes(){
    for(int i = 0; i < this->total_individuals; i++)
      this->individuals.push_back(Chromosomes::Chromosome(this->chromosome_size, this->total_points));
  }
  
  void Population::add_chromosomes(unsigned int total){
    for(int i = 0; i < total; i++)
      this->individuals.push_back(Chromosomes::Chromosome(this->chromosome_size, this->total_points));
  }

  void Population::reward_individual(Chromosomes::Chromosome chromosome, int reward){
    chromosome.update_points(reward); 
  }

  void Population::reward_all(std::vector<int> rewards){
    if(rewards.size() != this->total_individuals)
      throw std::invalid_argument("Invalid rewards size, it must be equals to the total of individuals!");

    for(int i = 0; i < this->total_individuals; i++){
      Chromosomes::Chromosome chromosome = this->individuals[i];
      chromosome.update_points(rewards[i]);
    }
  }

  void Population::new_generation(unsigned int top){
    this->individuals.erase(this->individuals.begin()+top, this->individuals.end());
    this->add_chromosomes(this->total_individuals - top);
  }

  std::vector<Chromosomes::Chromosome> Population::get_individuals(){
    return this->individuals;
  }

  void Population::show(){
    for(Chromosomes::Chromosome chromosome : this->individuals)
      chromosome.show();
  }
}
