#include "helpers/constants.h"
#include "game/food.h"
#include "game/gui.h"
#include "game/player.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_timer.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "matrix/matrix.h"

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
  
  char *title = (char*) malloc(10*sizeof(char));
  strcpy(title, "snake game");
  GUI::Game *game = new GUI::Game(title, WIDTH, HEIGHT);

  while(!game->event_close()){
    game->listen_event();
    
    Players::Player* player = game->get_player();
    
    if(game->event_keydown()){      
      if(game->event_move(SDLK_w))
        player->direction_up();
      else if(game->event_move(SDLK_s))
        player->direction_down();
      else if(game->event_move(SDLK_d))
        player->direction_right();
      else if(game->event_move(SDLK_a))
        player->direction_left();
    }
    player->update_position();

    if(player->is_game_over()){
      std::cout << "game over" << std::endl;
      break;
    }
    if(player->has_won()){
      std::cout << "WONWNWNWNWNW" << std::endl;
      break;
    }

    Foods::Food *food = game->get_food();
    if(player->collision(food->get_x(), food->get_y())){
      game->regenerate_food();
      player->update_score();
      std::cout << "Player score: " << player->get_score() << std::endl;
    }
    game->clear_screen();
    game->render_food();
    game->render_player();
    game->show();
  }

  delete title;
  delete game;
  /*
  Matrices::Matrix* matrix_1 = new Matrices::Matrix(3, 1);
  Matrices::Matrix* matrix_2 = new Matrices::Matrix(2, 3);
  
  matrix_1->update_value(0, 0, 1);
  matrix_1->update_value(0, 1, 2);
  matrix_1->update_value(0, 2, 3);
   
  matrix_1->show();
  matrix_2->update_value(0, 0, 1);
  matrix_2->update_value(0, 1, 2);
  matrix_2->update_value(1, 0, 1);
  matrix_2->update_value(1, 1, 2);
  matrix_2->update_value(2, 0, 1);
  matrix_2->update_value(2, 1, 2);
  matrix_2->show();
  std::cout << std::endl;
  
  Matrices::Matrix result = (*matrix_1) * (*matrix_2);
  result.show();


  delete matrix_1;
  delete matrix_2;
  */
  return 0;
}
