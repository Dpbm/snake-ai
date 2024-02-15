#include <iostream>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include "player_screen.h"
#include "screens.h"
#include "../player.h"
#include "../food.h"

using std::cout;
using std::endl;
using Screens::Screen;
using Players::Player;
using Foods::Food;


namespace GamePlayerScreen{
  Player* player; 
  Food* food = new Food;
  unsigned int max_score;

  Screen* PlayerScreen::key_event(const SDL_Keycode& key){
    switch (key) {
      case SDLK_w:
        this->player->direction_up();
        break;

      case SDLK_s:
        this->player->direction_down();
        break;

      case SDLK_d:
        this->player->direction_right();
        break;

      case SDLK_a:
        this->player->direction_left();
        break;

      default: break;
    }
    return nullptr;
  }

  void PlayerScreen::execute(SDL_Renderer* render, bool& game_loop){
    this->player->update_position();

    if(this->player->is_die()){
      cout << "GAME OVER!" << endl;
      game_loop = false;
    }else if(this->player->get_score() >= this->max_score){
      cout << "WON!" << endl;
      game_loop = false;
    }
    
    if(this->player->collision(this->food->get_x(), this->food->get_y())){
      this->food->update_position();
      this->player->update_score();
      cout << "Player score: " << this->player->get_score() << endl;
    }

    this->food->render(render);
    this->player->render(render);
  } 
  
  PlayerScreen::~PlayerScreen(){
    delete this->food;
    delete this->player;
  }
}
