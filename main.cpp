#include <iostream>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_ttf.h>
#include "helpers/constants.h"
#include "game/screens/screens.h"
#include "game/screens/start_screen.h"

using std::cout;
using std::endl;
using Screens::Screen;
using Screens::StartScreen;

int main(){
  setlocale(LC_ALL, "en_US.UTF-8");
  setlocale(LC_NUMERIC, "en_US.UTF-8");
  
  if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
    cout << "SDL_Init Error: " << SDL_GetError() << endl;
    return 1;
  }
  if(TTF_Init() == -1){
    cout << "TTF_Init Error: " << TTF_GetError() << endl;
    return 1;
  }

  SDL_Window* window = SDL_CreateWindow(
    "snake game", 
    SDL_WINDOWPOS_UNDEFINED, 
    SDL_WINDOWPOS_UNDEFINED, 
    WIDTH, 
    HEIGHT, 
    SDL_WINDOW_ALLOW_HIGHDPI);
  if(window == nullptr){
    cout << "Failed on create window: " << TTF_GetError() << endl;
    return 1;
  }

  SDL_Renderer* render = SDL_CreateRenderer(window, 1, 0);
  if(render == nullptr){
    cout << "Failed on create render: " << TTF_GetError() << endl;
    return 1;
  }

  Screen* screen = new StartScreen(render);
  bool game_loop = true;

  while(game_loop){
    SDL_Event event;
    while(SDL_PollEvent(&event)){ 
      if(event.type == SDL_QUIT) 
        game_loop = false;
      else if(event.type == SDL_KEYDOWN){
        if(event.key.keysym.sym == SDLK_ESCAPE) 
          game_loop = false;
        
        Screen* changed_screen = screen->key_event(event.key.keysym.sym);
        if(changed_screen != nullptr){
          delete screen;
          screen = changed_screen;
          continue;
        }
      }
    }
    SDL_RenderClear(render);
    screen->execute(game_loop);
    SDL_RenderPresent(render);
  }

  screen->close_event();
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(render);
  SDL_Quit();
  TTF_Quit();
  delete screen;

  return 0;
}
