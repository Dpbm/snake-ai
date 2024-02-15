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
#include "game/screens/screens.h"
#include "game/screens/start_screen.h"

using std::cout;
using std::endl;
using Foods::Food;
using Players::Player;
using Screens::Screen;
using GameStartScreen::StartScreen;

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
  Screen* screen = new StartScreen(render);

  bool game_loop = true;

  while(game_loop){
    SDL_PollEvent(event);
    
    if(event->type == SDL_QUIT) 
      break;
    else if(event->type == SDL_KEYDOWN){
      if(event->key.keysym.sym == SDLK_ESCAPE) 
        break;
      
      Screen* changed_screen = screen->key_event(event->key.keysym.sym);
      if(changed_screen != nullptr){
        delete screen;
        screen = changed_screen;
        continue;
      }
    }

    SDL_RenderClear(render);
    screen->execute(render, game_loop);
    SDL_RenderPresent(render);
  }

  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(render);
  SDL_Quit();
  TTF_Quit();
  delete screen;
  delete event;

  return 0;
}
