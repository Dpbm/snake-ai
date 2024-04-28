#include <SDL2/SDL_timer.h>
#include <cstddef>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_stdinc.h>
#include <cstdint>
#include <iostream>
#include <string>
#include "screens.h"
#include "ai_screen.h"
#include "../../helpers/constants.h"
#include "../../genetic/population.h"

using std::to_string;
using std::cout;
using std::endl;
using std::size_t;
using Genetic::Individual;

namespace Screens {

  AIScreen::AIScreen(SDL_Renderer* render){
    if(!this->font){
      cout << "Failed on getting font!" << TTF_GetError() << endl;
      exit(1);
    }

    this->render = render;

    SDL_Surface* score_text_surface = TTF_RenderText_Solid(this->font, "Best Score", this->text_color);
    this->score_text_texture = SDL_CreateTextureFromSurface(render, score_text_surface);
    this->score_text_shape = SDL_Rect{20, 20, score_text_surface->w, score_text_surface->h};
    SDL_FreeSurface(score_text_surface);
    
    SDL_Surface* gen_text_surface = TTF_RenderText_Solid(this->font, "Generation", this->text_color);
    this->gen_text_texture = SDL_CreateTextureFromSurface(render, gen_text_surface);
    this->gen_text_shape = SDL_Rect{20, 90, gen_text_surface->w, gen_text_surface->h};
    SDL_FreeSurface(gen_text_surface);
    
    SDL_Surface* alive_text_surface = TTF_RenderText_Solid(this->font, "Alive", this->text_color);
    this->alive_text_texture = SDL_CreateTextureFromSurface(render, alive_text_surface);
    this->alive_text_shape = SDL_Rect{20, 160, alive_text_surface->w, alive_text_surface->h};
    SDL_FreeSurface(alive_text_surface);
    
    SDL_Surface* fitness_text_surface = TTF_RenderText_Solid(this->font, "Fitness", this->text_color);
    this->fitness_text_texture = SDL_CreateTextureFromSurface(render, fitness_text_surface);
    this->fitness_text_shape = SDL_Rect{20, 230, fitness_text_surface->w, fitness_text_surface->h};
    SDL_FreeSurface(fitness_text_surface);
    
    SDL_Surface* timer_text_surface = TTF_RenderText_Solid(this->font, "Timer", this->text_color);
    this->timer_text_texture = SDL_CreateTextureFromSurface(render, timer_text_surface);
    this->timer_text_shape = SDL_Rect{20, 300, timer_text_surface->w, timer_text_surface->h};
    SDL_FreeSurface(timer_text_surface);

    if(this->score_text_texture == nullptr || 
       this->gen_text_texture == nullptr || 
       this->alive_text_texture == nullptr ||
       this->fitness_text_texture == nullptr ||
       this->timer_text_texture == nullptr){
      cout << "Failed on creating text textures!" << SDL_GetError() << endl;
      exit(1);
    }

    this->control_tick = SDL_GetTicks();
  }

  void AIScreen::execute(SDL_Renderer* render, bool& game_loop){
    uint8_t actual_time = (SDL_GetTicks() - this->control_tick)/1000;

    this->population.run();

    Individual* best_ind_alive = this->population.get_best_alive_individual();
    AIPlayer* player = best_ind_alive->player;
    Board* board = best_ind_alive->board;

    uint8_t** board_m = board->get_board();
    for(size_t i = 0; i < this->board_h; i++)
      for(size_t j = 0; j < this->board_w; j++){
        SDL_Rect rect = SDL_Rect{(int)((j*SQUARE_SIDE)+this->left_padding), (int)i*SQUARE_SIDE, SQUARE_SIDE, SQUARE_SIDE};
        switch(board_m[i][j]){
          case 0: {
            SDL_SetRenderDrawColor(render, 100, 100, 100, 255);
            SDL_RenderDrawRect(render, &rect);
            break;
          }
          
          case 1: {
            SDL_SetRenderDrawColor(render, 0, 0, 255, 255);
            SDL_RenderFillRect(render, &rect);
            break;
          }
        
          case 2: {
            SDL_SetRenderDrawColor(render, 0, 255, 0, 255);
            SDL_RenderFillRect(render, &rect);
            break;
          }

          default: break;
        }
      }


    SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
    SDL_RenderCopy(render, this->score_text_texture, NULL, &this->score_text_shape);
    SDL_RenderCopy(render, this->gen_text_texture, NULL, &this->gen_text_shape);
    SDL_RenderCopy(render, this->alive_text_texture, NULL, &this->alive_text_shape);
    SDL_RenderCopy(render, this->fitness_text_texture, NULL, &this->fitness_text_shape);
    SDL_RenderCopy(render, this->timer_text_texture, NULL, &this->timer_text_shape);
    
    if(this->score_texture != nullptr)
      SDL_DestroyTexture(this->score_texture);
   
    SDL_Surface* score_surface = TTF_RenderText_Solid(this->font, to_string(this->population.get_best_score()).c_str(), this->text_color);
    this->score_texture = SDL_CreateTextureFromSurface(render, score_surface);
    this->score_shape = SDL_Rect{this->score_text_shape.x, this->score_text_shape.y+30, score_surface->w, score_surface->h};
    SDL_FreeSurface(score_surface);
    
    if(this->gen_texture != nullptr)
      SDL_DestroyTexture(this->gen_texture);
    
    SDL_Surface* gen_surface = TTF_RenderText_Solid(this->font, to_string(this->population.get_gen()).c_str(), this->text_color);
    this->gen_texture = SDL_CreateTextureFromSurface(render, gen_surface);
    this->gen_shape = SDL_Rect{this->gen_text_shape.x, this->gen_text_shape.y+30, gen_surface->w, gen_surface->h};
    SDL_FreeSurface(gen_surface);
    
    if(this->alive_texture != nullptr)
      SDL_DestroyTexture(this->alive_texture);
    
    SDL_Surface* alive_surface = TTF_RenderText_Solid(this->font, to_string(this->population.get_total_alive()).c_str(), this->text_color);
    this->alive_texture = SDL_CreateTextureFromSurface(render, alive_surface);
    this->alive_shape = SDL_Rect{this->alive_text_shape.x, this->alive_text_shape.y+30, alive_surface->w, alive_surface->h};
    SDL_FreeSurface(alive_surface);
    
    if(this->fitness_texture != nullptr)
      SDL_DestroyTexture(this->fitness_texture);
    
    SDL_Surface* fitness_surface = TTF_RenderText_Solid(this->font, to_string(this->population.get_best_fitness()).c_str(), this->text_color);
    this->fitness_texture = SDL_CreateTextureFromSurface(render, fitness_surface);
    this->fitness_shape = SDL_Rect{this->fitness_text_shape.x, this->fitness_text_shape.y+30, fitness_surface->w, fitness_surface->h};
    SDL_FreeSurface(fitness_surface);
    
    if(this->timer_texture != nullptr)
      SDL_DestroyTexture(this->timer_texture);
    
    SDL_Surface* timer_surface = TTF_RenderText_Solid(this->font, to_string(actual_time).c_str(), this->text_color);
    this->timer_texture = SDL_CreateTextureFromSurface(render, timer_surface);
    this->timer_shape = SDL_Rect{this->timer_text_shape.x, this->timer_text_shape.y+30, timer_surface->w, timer_surface->h};
    SDL_FreeSurface(timer_surface);

    SDL_RenderCopy(render, this->score_texture, NULL, &this->score_shape);
    SDL_RenderCopy(render, this->gen_texture, NULL, &this->gen_shape);
    SDL_RenderCopy(render, this->alive_texture, NULL, &this->alive_shape);
    SDL_RenderCopy(render, this->fitness_texture, NULL, &this->fitness_shape);
    SDL_RenderCopy(render, this->timer_texture, NULL, &this->timer_shape);
    
    if(actual_time > this->gen_time){
      this->control_tick = SDL_GetTicks();
    }
  }

  Screen* AIScreen::key_event(const SDL_Keycode& key){
    return nullptr;
  }

  void AIScreen::close_event(){
  }
  
  AIScreen::~AIScreen(){
    SDL_DestroyTexture(this->score_texture);
    SDL_DestroyTexture(this->score_text_texture);
    SDL_DestroyTexture(this->gen_texture);
    SDL_DestroyTexture(this->gen_text_texture);
    SDL_DestroyTexture(this->alive_texture);
    SDL_DestroyTexture(this->alive_text_texture);
    SDL_DestroyTexture(this->fitness_texture);
    SDL_DestroyTexture(this->fitness_text_texture);
    SDL_DestroyTexture(this->timer_texture);
    SDL_DestroyTexture(this->timer_text_texture);
  }
}
