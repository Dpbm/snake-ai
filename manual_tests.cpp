#include <cstddef>
#include <vector>
#include <iostream>
#include "./genetic/gene.h"
#include "./genetic/chromosome.h"
#include "./matrix/matrix.h"
#include "./machine/layer.h"
#include "./machine/activation.h"
#include "./machine/machine.h"
#include "./helpers/utils.h"
#include "./game/players/player.h"

using std::vector;
using std::size_t;
using std::cout;
using std::endl;
using Genes::Gene;
using Chromosomes::Chromosome;
using Machine::Layer;
using Machine::NN;
using Matrices::Matrix;
using Utils::random;
using Utils::parse_weigths;
using Utils::parse_nn;
using Players::Player;
using Players::Directions;

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
  // vector<Matrix*> result = parse_weigths("test.wg");
  parse_nn("test.wg");
  // for(Matrix* m : result){
  //   cout << endl;
  //   m->show();
  //  } 


  cout << endl << "---PLAYERS---" << endl;
  for(size_t i = 0; i < 10; i++){
    Player p{1, 0, 0, Directions::RIGHT};
    p.update_pos();
    cout << "x: " << p.get_x() << " y: " << p.get_y() << endl;
  }
}

