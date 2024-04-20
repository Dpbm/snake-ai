#include <SDL2/SDL_timer.h>
#include <cstddef>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_stdinc.h>
#include <iostream>
#include "screens.h"
#include "ai_screen.h"
#include "../../helpers/constants.h"
#include "../../genetic/population.h"

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

    SDL_Surface* score_text_surface = TTF_RenderText_Solid(this->font, "Score", this->text_color);
    this->score_text_texture = SDL_CreateTextureFromSurface(render, score_text_surface);
    this->score_text_shape = SDL_Rect{20, 20, score_text_surface->w, score_text_surface->h};
    SDL_FreeSurface(score_text_surface);
    
    SDL_Surface* gen_text_surface = TTF_RenderText_Solid(this->font, "Generation", this->text_color);
    this->gen_text_texture = SDL_CreateTextureFromSurface(render, gen_text_surface);
    this->gen_text_shape = SDL_Rect{20, 90, gen_text_surface->w, gen_text_surface->h};
    SDL_FreeSurface(score_text_surface);

    if(this->score_text_texture == nullptr){
      cout << "Failed on creating score text texture!" << SDL_GetError() << endl;
      exit(1);
    }
  }

  void AIScreen::execute(SDL_Renderer* render, bool& game_loop){
    Individual* best_ind = this->population.get_best_individual();
    AIPlayer* player = best_ind->player;
    Board* board = best_ind->board;

    player->update_input_data(board->get_food(), this->board_w, this->board_h);
    player->compute_next_dir();
    player->update_dir();

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
    
    if(this->score_texture != nullptr)
      SDL_DestroyTexture(this->score_texture);
    
    SDL_Surface* score_surface = TTF_RenderText_Solid(this->font, "0"/*CHANGE HERE*/, this->text_color);
    this->score_texture = SDL_CreateTextureFromSurface(render, score_surface);
    this->score_shape = SDL_Rect{this->score_text_shape.x, this->score_text_shape.y+30, score_surface->w, score_surface->h};
    SDL_FreeSurface(score_surface);
    
    if(this->gen_texture != nullptr)
      SDL_DestroyTexture(this->gen_texture);
    
    SDL_Surface* gen_surface = TTF_RenderText_Solid(this->font, "1"/*CHANGE HERE*/, this->text_color);
    this->gen_texture = SDL_CreateTextureFromSurface(render, gen_surface);
    this->gen_shape = SDL_Rect{this->gen_text_shape.x, this->gen_text_shape.y+30, gen_surface->w, gen_surface->h};
    SDL_FreeSurface(gen_surface);

    SDL_RenderCopy(render, this->score_texture, NULL, &this->score_shape);
    SDL_RenderCopy(render, this->gen_texture, NULL, &this->gen_shape);
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
  }
}
