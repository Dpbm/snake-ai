#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include "helpers/constants.h"
#include "game/food.h"

using Foods::Food;

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

  while(true){
    SDL_PollEvent(event);

    if(event->type == SDL_QUIT) 
      break;
    
    
    SDL_RenderClear(render);
    food->render(render);
    SDL_RenderPresent(render);
  }

  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(render);
  SDL_Quit();
  delete event;
  delete food;
    //TODO: change to switch case
    /*if(game->event_keydown()){      
      if(game->event_move(SDLK_w))
        player->direction_up();
      else if(game->event_move(SDLK_s))
        player->direction_down();
      else if(game->event_move(SDLK_d))
        player->direction_right();
      else if(game->event_move(SDLK_a))
        player->direction_left();
    }*/
    //player->update_position();

    /*if(player->is_game_over()){
      cout << "game over" << endl;
      break;
    }
    if(player->has_won()){
      cout << "WONWNWNWNWNW" << endl;
      break;
    }

    if(player->collision(food->get_x(), food->get_y())){
      game->regenerate_food();
      player->update_score();
      cout << "Player score: " << player->get_score() << endl;
    }*/
   // game->render_player();

  
  return 0;
}
