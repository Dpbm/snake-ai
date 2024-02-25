#include <iostream>
#include "./genetic/gene.h"
#include "./genetic/chromosome.h"
#include "./genetic/population.h"

using std::cout;
using std::endl;
using Genes::Gene;
using Populations::Population;
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
  Chromosome* ch1 = new Chromosome(10, 100);
  Chromosome* ch2 = new Chromosome(10, 100);
  ch1->show();
  ch2->show();
  delete ch1;
  delete ch2;

  cout << "!!!!Creating a chromosomes array to test if their values are different!!!!" << endl;
  Chromosome* chromosomes = new Chromosome[3];
  chromosomes[0].add_genes(10, 100);
  chromosomes[1].add_genes(10, 100);
  chromosomes[2].add_genes(10, 100);
  chromosomes[0].show();
  chromosomes[1].show();
  chromosomes[2].show();
  delete[] chromosomes;


  cout << endl << "---POPULATION---" << endl;
  cout << "!!!!Creating a population to check if each individual have different chromosomes!!!!" << endl;
  Population* p = new Population(3, 10, 100);
  p->show();
  delete p;
}
