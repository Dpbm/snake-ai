#include <iostream>
#include "utils.h"
#include "gene.h"

namespace Genes {
  unsigned int value;
  
  Gene::Gene(){
    this->Gene::rand_gene_value();
  }

  unsigned int Gene::get_gene_value(){
    return this->Gene::value;
  }

  void Gene::set_gene_value(unsigned int value){
    if(value != 0 && value != 1)
      throw std::invalid_argument("Invalid gene value! Accepted: {0, 1}");
    this->value = value;
  }

  void Gene::mutate(float rate){
    if(rate < 0 || rate > 1)
      throw std::invalid_argument("Invalid mutation rate! Accepted from 0 to 1");

    unsigned int rand = Utils::random(1, 100);
    bool mutate = rand <= rate*100;
    std::cout << "mutate: " << mutate << " rand_val: " << rand; 
    if(mutate) this->Gene::rand_gene_value();
    else std::cout << std::endl;
  }
          

  void Gene::rand_gene_value(){
    std::cout << " before: " << this->value;
    this->value = Utils::random(0, 1);
    std::cout << " after: " << this->value << std::endl;
  }
}
