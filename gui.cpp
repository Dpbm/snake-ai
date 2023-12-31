#include "gui.h"
#include "constants.h"
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
  int last_event_tick;

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

  bool Game::event_close(){
    return this->event->type == SDL_QUIT;
  }

  void Game::update_last_tick(){
    this->last_event_tick = SDL_GetTicks();
  }

  bool Game::passed_debounce_time(){
    return  SDL_GetTicks() - this->last_event_tick >= DEBOUNCE_TIME;
  }

  bool Game::event_keydown(){
    return this->event->type == SDL_KEYDOWN;
  }  

  bool Game::pressed_that_key(SDL_Keycode key){
    return this->Game::passed_debounce_time() && this->event->key.keysym.sym == key;
  }

  bool Game::event_move(SDL_Keycode key){
    bool handle = this->Game::pressed_that_key(key);
    if(handle) this->Game::update_last_tick();
    return handle;
  }

  Foods::Food* Game::get_food(){
    return this->food;
  }

  void Game::regenerate_food(){
    delete this->food;
    this->food = new Foods::Food();
  }
}
