#include <iostream>
#include "../helpers/utils.h"
#include "gene.h"

namespace Genes {
  double value;
  
  Gene::Gene(){
    this->Gene::rand_gene_value();
  }

  double Gene::get_gene_value(){
    return this->value;
  }

  void Gene::set_gene_value(double value){
    this->value = value;
  }

  void Gene::mutate(float rate){
    if(rate < 0 || rate > 1)
      throw std::invalid_argument("Invalid mutation rate! Accepted from 0 to 1");

    unsigned int rand = Utils::random(1, 100);
    bool mutate = rand <= rate*100;
    if(mutate) this->Gene::rand_gene_value();
  }
          
  void Gene::rand_gene_value(){
    this->value = Utils::random(-1, 1);
  }

  Genes::Gene* Gene::copy(){
    Genes::Gene* new_gene = new Genes::Gene;
    new_gene->set_gene_value(this->value);
    return new_gene;
  }
}
