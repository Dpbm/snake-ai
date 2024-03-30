#include <SDL2/SDL_surface.h>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include "player_screen.h"
#include "screens.h"

using std::cout;
using std::endl;

namespace Screens{
  PlayerScreen::PlayerScreen(SDL_Renderer* render){
    if(!this->font){
      cout << "Failed on getting font!" << TTF_GetError() << endl;
      exit(1);
    }

    SDL_Surface* score_text_surface = TTF_RenderText_Solid(this->font, "Score ", this->text_color);
    this->score_text_texture = SDL_CreateTextureFromSurface(render, score_text_surface);
    this->score_text_shape = SDL_Rect{20, 20, score_text_surface->w, score_text_surface->h};
    
    SDL_Surface* score_surface = TTF_RenderText_Solid(this->font, "0", this->text_color);
    this->score_texture = SDL_CreateTextureFromSurface(render, score_surface);
    this->score_shape = SDL_Rect{score_text_shape.w+20, 20, score_surface->w, score_surface->h};
    
    SDL_FreeSurface(score_text_surface);
    SDL_FreeSurface(score_surface);

    if(this->score_texture == nullptr || this->score_text_texture == nullptr){
      cout << "Failed on creating textures!" << SDL_GetError() << endl;
      exit(1);
    }
    this->board.add_player(&this->player);
  }


  Screen* PlayerScreen::key_event(const SDL_Keycode& key){
    switch (key) {
      case SDLK_w:
        this->player.direction_up();
        break;
        
      case SDLK_s:
        this->player.direction_down();
        break;
      
      case SDLK_a:
        this->player.direction_left();
        break;
      
      case SDLK_d:
        this->player.direction_right();
    }
    return nullptr;
  }

  void PlayerScreen::execute(SDL_Renderer* render, bool& game_loop){
    this->player.update_pos();
    this->board.update_player_pos();
    
    uint8_t** board = this->board.get_board();
    for(size_t i = 0; i < this->board_h; i++)
      for(size_t j = 0; j < this->board_w; j++){
        SDL_Rect rect = SDL_Rect{(int)((j*SQUARE_SIDE)+left_padding), (int)i*SQUARE_SIDE, SQUARE_SIDE, SQUARE_SIDE};
        switch(board[i][j]){
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
    SDL_RenderCopy(render, this->score_texture, NULL, &this->score_shape);

  } 
  
  void PlayerScreen::close_event(){}
  
  PlayerScreen::~PlayerScreen(){
    SDL_DestroyTexture(this->score_texture);
    SDL_DestroyTexture(this->score_text_texture);
  }
}
