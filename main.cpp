#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include <ostream>
#include <vector>
#include "chromosome.h"
#include "gene.h"
#include "population.h"
#include <SDL2/SDL.h>
#include "constants.h"

int main(){
  /**std::cout << "---Simple GA test---" << std::endl;
  
  unsigned int size = 10;
  Chromosomes::Chromosome chromosome = Chromosomes::Chromosome(size);
  chromosome.show();  

  std::cout << "---first---" << std::endl;
  chromosome.show();

  chromosome.mutate(0.5);
  std::cout << "---second---" << std::endl;
  chromosome.show();

  std::vector<Genes::Gene> genes = chromosome.slice(3, 8);
  for(Genes::Gene gene : genes){
    std::cout << "sliced : " << gene.get_gene_value() << std::endl;
  } 
*/

 /** unsigned int size = 10;
  Chromosomes::Chromosome ch1 = Chromosomes::Chromosome(size);
  Chromosomes::Chromosome ch2 = Chromosomes::Chromosome(size);

  std::cout << "---Chromossome 1---" << std::endl;
  ch1.show();
  std::cout << "---Chromossome 2---" << std::endl;
  ch2.show();
  std::cout << "crossover"<<std::endl;
  
  unsigned int start = 3;
  unsigned int end = 6;
  std::vector<Genes::Gene> slice = ch1.slice(start,end);
  for(Genes::Gene gene :slice){
    std::cout <<gene.get_gene_value() << " ";
  }
  std::cout << std::endl;


  ch2.crossover(start, end, slice);
  std::cout << "CH1" <<std::endl;
  ch1.show();

  std::cout << "CH2" <<std::endl;
  ch2.show();
**/

  /**
  Populations::Population population = Populations::Population(10, 5, 100);
  population.show();
  */

  if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
    std::cout << "Failed intializing SDL2!!" << std::endl;
    return 1;
  }

  SDL_Window *window =SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
  
  if(window == NULL){
    std::cout << "Failed on create window!" << std::endl;
    return 1;
  }

  SDL_Event event;

  while(true)
    if(SDL_PollEvent(&event) && SDL_QUIT == event.type) break;
  
  SDL_DestroyWindow(window);
  SDL_Quit();


  return 0;
}
