#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include "helpers/constants.h"
#include "game/player.h"
#include "game/food.h"

using std::cout;
using std::endl;
using Foods::Food;
using Players::Player;

int main(){
  //TODO: Check for SDL errors
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_Window* window = SDL_CreateWindow(
    "snake game", 
    SDL_WINDOWPOS_UNDEFINED, 
    SDL_WINDOWPOS_UNDEFINED, 
    WIDTH, 
    HEIGHT, 
    SDL_WINDOW_ALLOW_HIGHDPI);
  SDL_Renderer* render = SDL_CreateRenderer(window, 1, 0);
  SDL_Event *event = new SDL_Event;
  Food *food = new Food;

  unsigned int max_score = 1000;
  Player* player = new Player(10, max_score);

  while(true){
    SDL_PollEvent(event);

    if(event->type == SDL_QUIT) 
      break;
    else if(event->type == SDL_KEYDOWN){
      switch (event->key.keysym.sym) {
        case SDLK_w:
          player->direction_up();
          break;

        case SDLK_s:
          player->direction_down();
          break;

        case SDLK_d:
          player->direction_right();
          break;

        case SDLK_a:
          player->direction_left();
          break;

        default: break;
      }
    }    
    
    player->update_position();
   

    if(player->is_die()){
      cout << "GAME OVER!" << endl;
      break;
    }else if(player->get_score() >= max_score){
      cout << "WON!" << endl;
      break;
    }
    
    if(player->collision(food->get_x(), food->get_y())){
      food->update_position();
      player->update_score();
      cout << "Player score: " << player->get_score() << endl;
    }

    SDL_RenderClear(render);
    food->render(render);
    player->render(render);
    SDL_RenderPresent(render);
  }

  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(render);
  SDL_Quit();
  delete event;
  delete food;
  delete player;

  return 0;
}
