#include <iostream>
#include "./genetic/gene.h"
#include "./genetic/chromosome.h"

using std::cout;
using std::endl;
using Genes::Gene;
using Chromosomes::Chromosome;

int main(){
  cout << "---GENES---" << endl;
  cout << "!!!!Creating two genes arrays and checking if they have different values!!!!" << endl;
  Gene* genes = new Gene[10];
  for(unsigned int i = 0; i < 10; i++)
    cout << genes[i].get_gene_value() << " ";
  cout << endl;
  delete[] genes;

  Gene* genes2 = new Gene[10];
  for(unsigned int i = 0; i < 10; i++)
    cout << genes2[i].get_gene_value() << " ";
  cout << endl;
  delete[] genes2;


  cout << endl << "---CHROMOSOMES---" << endl;
  cout << "!!!!Creating 2 different chromosomes and checking if their values are different!!!!" << endl;
  Chromosome* ch1 = new Chromosome(10);
  Chromosome* ch2 = new Chromosome(10);
  ch1->show();
  ch2->show();
  delete ch1;
  delete ch2;
}
