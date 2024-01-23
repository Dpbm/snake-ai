#include "gui.h"
#include "../helpers/constants.h"
#include "food.h"
#include "player.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>

namespace GUI {
  int width, height;
  SDL_Window *window;
  SDL_Renderer *render;
  Foods::Food *food;
  Players::Player *player;
  SDL_Event *event;

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
    delete food;
    delete event;
    // TODO: to remove in the future
    player->free_player_mem();
    delete player;
  }

  void Game::listen_event(){
    SDL_PollEvent(this->event);
  }

  void Game::render_food(){
    SDL_Rect *rect = new SDL_Rect; 
    rect->x = this->food->get_x(); 
    rect->y = this->food->get_y();
    rect->h = FOOD_H;
    rect->w = FOOD_W;
    SDL_SetRenderDrawColor(this->render, 255, 255, 255, 255);
    SDL_RenderFillRect(this->render, rect);
    SDL_SetRenderDrawColor(this->render, 0, 0, 0, 255);
  }

  void Game::render_player(){
    Players::LinkedList* body = this->player->get_body();
    
    while(body != nullptr){
      SDL_Rect *rect = new SDL_Rect; 
      rect->x = body->value->get_x(); 
      rect->y = body->value->get_y();
      rect->h = PLAYER_H;
      rect->w = PLAYER_W;
      SDL_SetRenderDrawColor(this->render, 0, 0, 255, 255);
      SDL_RenderFillRect(this->render, rect);
      SDL_SetRenderDrawColor(this->render, 0, 0, 0, 255);

      body = body->next;
    }
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

  bool Game::event_close(){
    return this->event->type == SDL_QUIT;
  }

  bool Game::event_keydown(){
    return this->event->type == SDL_KEYDOWN;
  }  

  bool Game::event_move(SDL_Keycode key){
    return this->event->key.keysym.sym == key;
  }

  Foods::Food* Game::get_food(){
    return this->food;
  }

  void Game::regenerate_food(){
    delete this->food;
    this->food = new Foods::Food();
  }
}
