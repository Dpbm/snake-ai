#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_surface.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_ttf.h>
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
  TTF_Init();
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

  bool playing = true;
  unsigned int max_score = 1000;
  Player* player = new Player(10, max_score);
  
  TTF_Font* text_font = TTF_OpenFont("./assets/roboto.ttf", 16);
  if(!text_font){
    cout << "Failed on getting font!" << endl;
    cout << TTF_GetError() << endl;
    return 1;
  }

  SDL_Color Foreground = { 255, 255, 255 };
  SDL_Color Background = { 0, 0, 0 };
  
  SDL_Surface* text_surface = TTF_RenderText_Solid(text_font, "Hello world!", Foreground);
  SDL_Texture* text_texture = SDL_CreateTextureFromSurface(render, text_surface);
  SDL_FreeSurface(text_surface);

  SDL_Rect* text_shape = new SDL_Rect;
  text_shape->x = 10;
  text_shape->y = 10;
  text_shape->h = 200;
  text_shape->w = 200;

  while(playing){
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

        case SDLK_ESCAPE:
          playing = false;
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
    SDL_RenderCopy(render, text_texture, NULL, text_shape);
    food->render(render);
    player->render(render);
    SDL_RenderPresent(render);
  }

  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(render);
  SDL_DestroyTexture(text_texture);
  SDL_Quit();
  TTF_Quit();
  delete event;
  delete food;
  delete player;
  delete text_shape;

  return 0;
}
