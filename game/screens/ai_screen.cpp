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
#include "../players/ai_player.h"
#include "../../helpers/utils.h"
#include "../../helpers/constants.h"

using std::size_t;
using std::to_string;
using std::cout;
using std::endl;
using Screens::Screen;
using Players::Directions;
using Utils::get_random_x;
using Utils::get_random_y;

namespace GameAIScreen {

  AIScreen::AIScreen(SDL_Renderer* render){
    this->render = render;
    this->create_text();
    this->food.set_position(get_random_x(FOOD_W), get_random_y(FOOD_H));
  }




  void AIScreen::execute(SDL_Renderer* render, bool& game_loop){
    bool reset = this->population->run_population(this->food.get_x(), this->food.get_y());
  
    SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    SDL_RenderFillRect(render, &this->screen_separator);
    SDL_RenderCopy(render, this->score_text_texture, NULL, &this->score_text_shape);
    SDL_RenderCopy(render, this->score_texture, NULL, &this->score_shape);
    SDL_RenderCopy(render, this->generation_text_texture, NULL, &this->generation_text_shape);
    SDL_RenderCopy(render, this->generation_texture, NULL, &this->generation_shape);
    SDL_RenderCopy(render, this->individual_text_texture, NULL, &this->individual_text_shape);
    SDL_RenderCopy(render, this->individual_texture, NULL, &this->individual_shape);
    SDL_RenderCopy(render, this->best_individual_text_texture, NULL, &this->best_individual_text_shape);
    SDL_RenderCopy(render, this->best_individual_texture, NULL, &this->best_individual_shape);
    SDL_RenderCopy(render, this->best_pontuation_text_texture, NULL, &this->best_pontuation_text_shape);
    SDL_RenderCopy(render, this->best_pontuation_texture, NULL, &this->best_pontuation_shape);
    this->food.render(render);

    AIPlayer* players = this->population->get_individuals();
    for(size_t i = 0; i < this->population_size; i++)
      players[i].render(render);
  
    if(reset){
      this->food.set_position(get_random_x(FOOD_W), get_random_y(FOOD_H));
      this->population->next_generation();
    }
  }

  Screen* AIScreen::key_event(const SDL_Keycode& key){
    return nullptr;
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
    
    SDL_Surface* individual_text_surface = TTF_RenderText_Solid(this->font, "Indiv. ", this->text_color);
    this->individual_text_texture = SDL_CreateTextureFromSurface(this->render, individual_text_surface);
    this->individual_text_shape = SDL_Rect{20, 50, individual_text_surface->w, individual_text_surface->h};
    
    SDL_Surface* individual_surface = TTF_RenderText_Solid(this->font, "1", this->text_color);
    this->individual_texture = SDL_CreateTextureFromSurface(this->render, individual_surface);
    this->individual_shape = SDL_Rect{individual_text_shape.w+20, 50, individual_surface->w, individual_surface->h};
    
    SDL_Surface* generation_text_surface = TTF_RenderText_Solid(this->font, "Gen. ", this->text_color);
    this->generation_text_texture = SDL_CreateTextureFromSurface(this->render, generation_text_surface);
    this->generation_text_shape = SDL_Rect{20, 80, generation_text_surface->w, generation_text_surface->h};
    
    SDL_Surface* generation_surface = TTF_RenderText_Solid(this->font, "1", this->text_color);
    this->generation_texture = SDL_CreateTextureFromSurface(this->render, generation_surface);
    this->generation_shape = SDL_Rect{generation_text_shape.w+20, 80, generation_surface->w, generation_surface->h};
    
    SDL_Surface* best_individual_text_surface = TTF_RenderText_Solid(this->font, "Best ", this->text_color);
    this->best_individual_text_texture = SDL_CreateTextureFromSurface(this->render, best_individual_text_surface);
    this->best_individual_text_shape = SDL_Rect{20, 110, best_individual_text_surface->w, best_individual_text_surface->h};
    
    SDL_Surface* best_individual_surface = TTF_RenderText_Solid(this->font, "1", this->text_color);
    this->best_individual_texture = SDL_CreateTextureFromSurface(this->render, best_individual_surface);
    this->best_individual_shape = SDL_Rect{best_individual_text_shape.w+20, 110, best_individual_surface->w, best_individual_surface->h};
    
    SDL_Surface* best_pontuation_text_surface = TTF_RenderText_Solid(this->font, "Best pon. ", this->text_color);
    this->best_pontuation_text_texture = SDL_CreateTextureFromSurface(this->render, best_pontuation_text_surface);
    this->best_pontuation_text_shape = SDL_Rect{20, 140, best_pontuation_text_surface->w, best_pontuation_text_surface->h};
    
    SDL_Surface* best_pontuation_surface = TTF_RenderText_Solid(this->font, "0", this->text_color);
    this->best_pontuation_texture = SDL_CreateTextureFromSurface(this->render, best_pontuation_surface);
    this->best_pontuation_shape = SDL_Rect{best_pontuation_text_shape.w+20, 140, best_pontuation_surface->w, best_pontuation_surface->h};
    
    SDL_FreeSurface(score_text_surface);
    SDL_FreeSurface(score_surface);
    SDL_FreeSurface(generation_text_surface);
    SDL_FreeSurface(generation_surface);
    SDL_FreeSurface(individual_text_surface);
    SDL_FreeSurface(individual_surface);
    SDL_FreeSurface(best_individual_text_surface);
    SDL_FreeSurface(best_individual_surface);
    SDL_FreeSurface(best_pontuation_text_surface);
    SDL_FreeSurface(best_pontuation_surface);

    if(score_texture == nullptr ||
       score_text_texture == nullptr ||
       generation_text_texture == nullptr || 
       generation_texture == nullptr || 
       individual_text_texture == nullptr ||
       individual_texture == nullptr ||
       best_individual_text_surface == nullptr ||
       best_individual_texture == nullptr ||
       best_pontuation_text_texture == nullptr ||
       best_pontuation_texture == nullptr){
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
    SDL_DestroyTexture(this->individual_texture);
    SDL_DestroyTexture(this->individual_text_texture);
    SDL_DestroyTexture(this->best_individual_texture);
    SDL_DestroyTexture(this->best_individual_text_texture);
    SDL_DestroyTexture(this->best_pontuation_texture);
    SDL_DestroyTexture(this->best_pontuation_text_texture);
  }
}
