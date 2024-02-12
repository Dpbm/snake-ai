#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "game/gui.h"
#include "helpers/constants.h"
#include "game/food.h"
#include "game/player.h"

using std::cout;
using std::endl;
using GUI::Game;
using Players::Player;
using Foods::Food;

int main(){
  char *title = (char*) malloc(10*sizeof(char));
  strcpy(title, "snake game");
  Game *game = new Game(title, WIDTH, HEIGHT);

  while(!game->event_close()){
    game->listen_event();
    
    Player* player = game->get_player();
    
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
      cout << "game over" << endl;
      break;
    }
    if(player->has_won()){
      cout << "WONWNWNWNWNW" << endl;
      break;
    }

    Food *food = game->get_food();
    if(player->collision(food->get_x(), food->get_y())){
      game->regenerate_food();
      player->update_score();
      cout << "Player score: " << player->get_score() << endl;
    }
    game->clear_screen();
    game->render_food();
    game->render_player();
    game->show();
  }

  delete title;
  delete game;
  return 0;
}
