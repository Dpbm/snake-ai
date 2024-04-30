#include <cstddef>
#include <iostream>
#include "./genetic/gene.h"
#include "./genetic/chromosome.h"
#include "./matrix/matrix.h"
#include "./machine/layer.h"
#include "./machine/activation.h"
#include "./machine/machine.h"
#include "./helpers/utils.h"
#include "./game/players/player.h"
#include "genetic/population.h"

using std::size_t;
using std::cout;
using std::endl;
using Genes::Gene;
using Chromosomes::Chromosome;
using Machine::Layer;
using Machine::NN;
using Matrices::Matrix;
using Utils::random;
using Utils::parse_nn;
using Players::Player;
using Players::Directions;
using Genetic::Population;
using Genetic::Individual;

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

  cout << endl << "---MACHINE---" << endl;
  cout << "!!!!Testing if the NN is processing as expected!!!!" << endl;
  Matrix* input_data = new Matrix(2,1);
  input_data->update_value(0, 0, 0); //x
  input_data->update_value(0, 1, -10); //y

  NN* nn = new NN;
  Layer* input = new Layer(input_data, true);

  nn->add_layer(input);
  nn->add_layer(4);
  nn->add_layer(4);

  nn->get_layer(1)->relu();
  nn->get_layer(2)->sigmoid();

  Matrix* w0 = nn->get_weight(0)->get_weights();
  for(size_t i = 0; i < w0->get_height(); i++)
    for(size_t j = 0; j < w0->get_width(); j++)
      w0->update_value(i, j, random(-1,1));

  Matrix* w1 = nn->get_weight(1)->get_weights();
  for(size_t i = 0; i < w1->get_height(); i++)
    for(size_t j = 0; j < w1->get_width(); j++)
      w1->update_value(i, j, random(-1,1));

  nn->feedforward();

  nn->get_layer(0)->get_values()->show();
  cout << endl;
  nn->get_weight(0)->get_weights()->show();
  cout << endl;
  nn->get_layer(1)->get_values()->show();
  cout << endl;
  nn->get_weight(1)->get_weights()->show();
  cout << endl;
  nn->get_layer(2)->get_values()->show();
  //up down left right  

  delete nn;


  cout << endl << "---HELPERS---" << endl;
  cout << "!!!!Testing parsing weights file!!!!" << endl;
  NN* nn2 = parse_nn("test.wg");
  cout << "total layers: " << nn2->get_total_layers() << endl;
  cout << "total weights: " << nn2->get_total_weights() << endl;
  cout << "weights:" << endl; 
  nn2->get_weight(0)->get_weights()->show();
  delete nn2;

  cout << endl << "---PLAYERS---" << endl;
  for(size_t i = 0; i < 10; i++){
    Player p{0, 0, Directions::RIGHT};
    p.update_pos();
    cout << "x: " << p.get_x() << " y: " << p.get_y() << endl;
  }

  cout << endl << "---POPULATION---" << endl;
  cout << "!!!!testig select parents!!!!" << endl;
  Population p(3);
  Individual* ind1 = new Individual{nullptr, nullptr, 0, 0, Directions::LEFT, 0};
  Individual* ind2 = new Individual{nullptr, nullptr, 0, 0, Directions::LEFT, 0};
  Individual* ind3 = new Individual{nullptr, nullptr, 100, 0, Directions::LEFT, 0};

  p.append_individual(ind1);
  p.append_individual(ind2);
  p.append_individual(ind3);

  Individual** parents = p.select_parents();
  
  cout << "ind1 " << ind1 << endl;
  cout << "ind2 " << ind2 << endl;
  cout << "ind3 " << ind3 << endl;

  cout << "parent 1 " << parents[0] << endl;
  cout << "parent 2 " << parents[1] << endl;
  
  cout << endl << "!!!!testig generate offsping!!!!" << endl;
  Population p2(0);
  Chromosome chromosome1(10);
  Chromosome chromosome2(10);

  cout << "Chromosome 1: ";
  chromosome1.show();
  cout << "Chromosome 2: ";
  chromosome2.show();
  
  Chromosome* offsping = p2.generate_offspring(&chromosome1, &chromosome2);
  cout << "offsping: ";
  offsping->show();
  delete offsping;
}

