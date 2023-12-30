#include "gui.h"
#include "constants.h"
#include "player.h"
#include "utils.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

namespace GUI {
  int width, height;
  SDL_Window *window;
  SDL_Renderer *render;
  unsigned int food_x, food_y;
  Players::Player *player;

  Game::Game(char* title, int width, int height){
    SDL_Init(SDL_INIT_EVERYTHING);
    this->width = width;
    this->height = height;
    this->window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_ALLOW_HIGHDPI);
    this->render = SDL_CreateRenderer(this->window, 1, 0);
  }
  
  Game::~Game(){
    SDL_DestroyWindow(this->window);
    SDL_Quit();
  }

  SDL_Event Game::get_event(){
    SDL_Event event;
    SDL_PollEvent(&event);
    return event;
  }

  void Game::set_food_pos(){
    this->food_x = Utils::get_random_pos(WIDTH, FOOD_W);
    this->food_y = Utils::get_random_pos(HEIGHT, FOOD_H);
  }

  void Game::set_food_pos(unsigned int x, unsigned int y){
    this->food_x = x;
    this->food_y = y;
  }

  void Game::draw_food(){
    SDL_Rect *rect = new SDL_Rect; 
    rect->x = this->food_x; 
    rect->y = this->food_y;
    rect->h = FOOD_H;
    rect->w = FOOD_W;
    SDL_SetRenderDrawColor(this->render, 255, 255, 255, 255);
    SDL_RenderFillRect(this->render, rect);
    SDL_SetRenderDrawColor(this->render, 0, 0, 0, 255);
  }


  void Game::render_player(){
    SDL_Rect *rect = new SDL_Rect; 
    rect->x = player->get_x(); 
    rect->y = player->get_y();
    rect->h = PLAYER_H;
    rect->w = PLAYER_W;
    SDL_SetRenderDrawColor(this->render, 255, 0, 0, 255);
    SDL_RenderFillRect(this->render, rect);
    SDL_SetRenderDrawColor(this->render, 0, 0, 0, 255);
  }

  void Game::clear_screen(){
    SDL_RenderClear(this->render);
  }

  void Game::show(){
    SDL_RenderPresent(this->render);
  }

  Players::Player* Game::get_player(){
    return this->player;
  }  

 
}
