#include <SDL2/SDL_timer.h>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_stdinc.h>
#include "screens.h"
#include "ai_screen.h"
#include "../../helpers/constants.h"

using std::size_t;
using std::to_string;
using std::cout;
using std::endl;
using Screens::Screen;

namespace GameAIScreen {

  AIScreen::AIScreen(SDL_Renderer* render){
    this->render = render;
    this->create_text();
  }

  void AIScreen::execute(SDL_Renderer* render, bool& game_loop){
    uint8_t timer = (SDL_GetTicks() - this->start_tick)/1000; 
    
    bool reset = this->population->run_population();
   
    SDL_DestroyTexture(this->score_texture);
    SDL_DestroyTexture(this->best_individual_texture);
    SDL_DestroyTexture(this->timer_texture);
    
    SDL_Surface* score_surface = TTF_RenderText_Solid(this->font, to_string(this->population->get_best_score()).c_str(), this->text_color);
    this->score_texture = SDL_CreateTextureFromSurface(this->render, score_surface);
    this->score_shape = SDL_Rect{score_text_shape.w+20, 20, score_surface->w, score_surface->h};

    uint8_t best_player_i = this->population->get_best_fitness_i()+1;
    SDL_Surface* best_individual_surface = TTF_RenderText_Solid(this->font, to_string(best_player_i).c_str(), this->text_color);
    this->best_individual_texture = SDL_CreateTextureFromSurface(this->render, best_individual_surface);
    this->best_individual_shape = SDL_Rect{best_individual_text_shape.w+20, 80, best_individual_surface->w, best_individual_surface->h};
    
    SDL_Surface* timer_surface = TTF_RenderText_Solid(this->font, to_string(timer).c_str(), this->text_color);
    this->timer_texture = SDL_CreateTextureFromSurface(this->render, timer_surface);
    this->timer_shape = SDL_Rect{timer_text_shape.w+20, 110, timer_surface->w, timer_surface->h};
   
    SDL_FreeSurface(score_surface);
    SDL_FreeSurface(best_individual_surface);
    SDL_FreeSurface(timer_surface);
    
    if(
      this->score_texture == nullptr ||
      this->best_individual_texture == nullptr || 
      this->timer_texture == nullptr){
      cout << "Failed on adding textures!" << TTF_GetError() << endl;
      exit(1);
    }

    SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    SDL_RenderFillRect(render, &this->screen_separator);
    SDL_RenderCopy(render, this->score_text_texture, NULL, &this->score_text_shape);
    SDL_RenderCopy(render, this->score_texture, NULL, &this->score_shape);
    SDL_RenderCopy(render, this->generation_text_texture, NULL, &this->generation_text_shape);
    SDL_RenderCopy(render, this->generation_texture, NULL, &this->generation_shape);
    SDL_RenderCopy(render, this->best_individual_text_texture, NULL, &this->best_individual_text_shape);
    SDL_RenderCopy(render, this->best_individual_texture, NULL, &this->best_individual_shape);
    SDL_RenderCopy(render, this->timer_text_texture, NULL, &this->timer_text_shape);
    SDL_RenderCopy(render, this->timer_texture, NULL, &this->timer_shape);
    SDL_RenderCopy(render, this->see_all_texture, NULL, &this->see_all_shape);
    
    if(!this->see_all){
    
      AIPlayer* best_player_alive = this->population->get_best_player_alive();
      best_player_alive->render(render);
      best_player_alive->get_food()->render(render);

    }else{
      
      for(size_t i = 0; i < this->population_size; i++){
        AIPlayer* player = this->population->get_player(i);
        if(!player->is_dead()){
          player->render(render);
          player->get_food()->render(render);
        }
      }
    
    }

    if(reset || timer >= TOTAL_GENERATION_TIME){
      this->population->update_gen();

      SDL_DestroyTexture(this->generation_texture);
      SDL_Surface* generation_surface = TTF_RenderText_Solid(this->font, to_string(this->population->get_generation()).c_str(), this->text_color);
      this->generation_texture = SDL_CreateTextureFromSurface(this->render, generation_surface);
      this->generation_shape = SDL_Rect{generation_text_shape.w+20, 50, generation_surface->w, generation_surface->h};
      SDL_FreeSurface(generation_surface);
    
      if(this->generation_texture == nullptr){
        cout << "Failed on adding generation texture!" << TTF_GetError() << endl;
        exit(1);
      }
      
      this->population->next_generation();
      this->start_tick = SDL_GetTicks();
    }
  }

  Screen* AIScreen::key_event(const SDL_Keycode& key){
    if(key == SDLK_s)
      this->see_all = !this->see_all;

    return nullptr;
  }
 
  void AIScreen::close_event(){
    cout << "Saving weights..." << endl;
    this->population->save_weights();
  }

  void AIScreen::create_text(){
    if(!this->font){
      cout << "Failed on getting font!" << TTF_GetError() << endl;
      exit(1);
    }
    SDL_Surface* score_text_surface = TTF_RenderText_Solid(this->font, "Score ", this->text_color);
    this->score_text_texture = SDL_CreateTextureFromSurface(this->render, score_text_surface);
    this->score_text_shape = SDL_Rect{20, 20, score_text_surface->w, score_text_surface->h};
   
    SDL_Surface* score_surface = TTF_RenderText_Solid(this->font, "0", this->text_color);
    this->score_texture = SDL_CreateTextureFromSurface(this->render, score_surface);
    this->score_shape = SDL_Rect{score_text_shape.w+20, 20, score_surface->w, score_surface->h};
    
    SDL_Surface* generation_text_surface = TTF_RenderText_Solid(this->font, "Gen. ", this->text_color);
    this->generation_text_texture = SDL_CreateTextureFromSurface(this->render, generation_text_surface);
    this->generation_text_shape = SDL_Rect{20, 50, generation_text_surface->w, generation_text_surface->h};
    
    SDL_Surface* generation_surface = TTF_RenderText_Solid(this->font, "1", this->text_color);
    this->generation_texture = SDL_CreateTextureFromSurface(this->render, generation_surface);
    this->generation_shape = SDL_Rect{generation_text_shape.w+20, 50, generation_surface->w, generation_surface->h};
    
    SDL_Surface* best_individual_text_surface = TTF_RenderText_Solid(this->font, "Best ", this->text_color);
    this->best_individual_text_texture = SDL_CreateTextureFromSurface(this->render, best_individual_text_surface);
    this->best_individual_text_shape = SDL_Rect{20, 80, best_individual_text_surface->w, best_individual_text_surface->h};
    
    SDL_Surface* best_individual_surface = TTF_RenderText_Solid(this->font, "1", this->text_color);
    this->best_individual_texture = SDL_CreateTextureFromSurface(this->render, best_individual_surface);
    this->best_individual_shape = SDL_Rect{best_individual_text_shape.w+20, 80, best_individual_surface->w, best_individual_surface->h};
    
    SDL_Surface* timer_text_surface = TTF_RenderText_Solid(this->font, "Timer ", this->text_color);
    this->timer_text_texture = SDL_CreateTextureFromSurface(this->render, timer_text_surface);
    this->timer_text_shape = SDL_Rect{20, 110, timer_text_surface->w, timer_text_surface->h};
    
    SDL_Surface* timer_surface = TTF_RenderText_Solid(this->font, "0", this->text_color);
    this->timer_texture = SDL_CreateTextureFromSurface(this->render, timer_surface);
    this->timer_shape = SDL_Rect{timer_text_shape.w+20, 110, timer_surface->w, timer_surface->h};
    
    SDL_Surface* see_all_surface = TTF_RenderText_Solid(this->font, "'S' to see all ", this->text_color);
    this->see_all_texture = SDL_CreateTextureFromSurface(this->render, see_all_surface);
    this->see_all_shape = SDL_Rect{10, 160, see_all_surface->w, see_all_surface->h};
    
    SDL_FreeSurface(score_text_surface);
    SDL_FreeSurface(score_surface);
    SDL_FreeSurface(generation_text_surface);
    SDL_FreeSurface(generation_surface);
    SDL_FreeSurface(best_individual_text_surface);
    SDL_FreeSurface(best_individual_surface);
    SDL_FreeSurface(timer_text_surface);
    SDL_FreeSurface(timer_surface);
    SDL_FreeSurface(see_all_surface);

    if(score_texture == nullptr ||
       score_text_texture == nullptr ||
       generation_text_texture == nullptr || 
       generation_texture == nullptr || 
       best_individual_text_surface == nullptr ||
       best_individual_texture == nullptr ||
       timer_text_texture == nullptr ||
       timer_texture == nullptr ||
       see_all_texture == nullptr){
      cout << "Failed on adding textures!" << TTF_GetError() << endl;
      exit(1);
      
    }
  }
  
  AIScreen::~AIScreen(){
    this->clear_textures();
    delete this->population;
  }

  void AIScreen::clear_textures(){
    SDL_DestroyTexture(this->score_texture);
    SDL_DestroyTexture(this->score_text_texture);
    SDL_DestroyTexture(this->generation_texture);
    SDL_DestroyTexture(this->generation_text_texture);
    SDL_DestroyTexture(this->best_individual_texture);
    SDL_DestroyTexture(this->best_individual_text_texture);
    SDL_DestroyTexture(this->timer_texture);
    SDL_DestroyTexture(this->timer_text_texture);
    SDL_DestroyTexture(this->see_all_texture);
  }
}
