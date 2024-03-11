#include <stdexcept>
#include "../helpers/utils.h"
#include "gene.h"

using std::invalid_argument;
using Utils::random;

namespace Genes {
  double value; 

  Gene::Gene(){
    this->rand_gene_value();
  }

  double Gene::get_gene_value(){
    return this->value;
  }

  void Gene::set_gene_value(double value){
    this->value = value;
  }

  void Gene::mutate(float rate){
    if(rate < 0 || rate > 1)
      throw invalid_argument("Invalid mutation rate! Accepted from 0 to 1");

    unsigned int rand = random(1, 100);
    if(rand <= rate*100) this->rand_gene_value();
  }
          
  void Gene::rand_gene_value(){
    this->value = random(-800, 800);
  }

  void Gene::operator= (double value){
    this->value = value;
  }


  double Gene::operator+ (double value){
    return this->value + value;
  }

  double Gene::operator* (double value){
    return this->value*value;
  }

  
}
