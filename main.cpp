#include <iostream>
#include "gene.h"

int main(){
  std::cout << "---Simple GA test---" << std::endl;
  
  Genes::Gene first_gene;
   
  std::cout << "First gene value: " << first_gene.get_gene_value() << std::endl;

  return 0;
}
