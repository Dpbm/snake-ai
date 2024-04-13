#include <SDL2/SDL_surface.h>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "player_screen.h"
#include "screens.h"
#include "start_screen.h"

using std::cout;
using std::endl;
using std::to_string;

namespace Screens{
  PlayerScreen::PlayerScreen(SDL_Renderer* render){
    if(!this->font){
      cout << "Failed on getting font!" << TTF_GetError() << endl;
      exit(1);
    }
    this->render = render;

    SDL_Surface* score_text_surface = TTF_RenderText_Solid(this->font, "Score", this->text_color);
    this->score_text_texture = SDL_CreateTextureFromSurface(render, score_text_surface);
    this->score_text_shape = SDL_Rect{20, 20, score_text_surface->w, score_text_surface->h};
    SDL_FreeSurface(score_text_surface);

    if(this->score_text_texture == nullptr){
      cout << "Failed on creating score text texture!" << SDL_GetError() << endl;
      exit(1);
    }

    this->board.add_player(this->player);
  }


  Screen* PlayerScreen::key_event(const SDL_Keycode& key){
    switch (key) {
      case SDLK_w:
        this->player->direction_up();
        break;
        
      case SDLK_s:
        this->player->direction_down();
        break;
      
      case SDLK_a:
        this->player->direction_left();
        break;
      
      case SDLK_d:
        this->player->direction_right();
        break;

      case SDLK_g:
        if(this->finished_game) 
          return new StartScreen(this->render);

      case SDLK_r:
        if(this->finished_game) 
          this->reset();

      default:
        break;
    }
    return nullptr;
  }

  void PlayerScreen::execute(SDL_Renderer* render, bool& game_loop){
    bool won = this->player->get_score() >= this->max_score; 
    this->finished_game = won || this->player->is_dead();
    if(this->finished_game){
      SDL_Surface* game_over_surface = TTF_RenderText_Solid(this->title_font, won ? "Player Wins!!!" : "Game Over", this->text_color);
      SDL_Texture* game_over_texture = SDL_CreateTextureFromSurface(render, game_over_surface);
      SDL_Rect game_over_shape = SDL_Rect{(WIDTH/2)-(game_over_surface->w/2), (HEIGHT/2)-(game_over_surface->h), game_over_surface->w, game_over_surface->h};
      SDL_FreeSurface(game_over_surface);
      
      SDL_Surface* reset_surface = TTF_RenderText_Solid(this->font, "Press 'r' to reset", this->text_color);
      SDL_Texture* reset_texture = SDL_CreateTextureFromSurface(render, reset_surface);
      SDL_Rect reset_shape = SDL_Rect{(WIDTH/2)-(reset_surface->w/2), (HEIGHT/2)+(reset_surface->h)+20, reset_surface->w, reset_surface->h};
      SDL_FreeSurface(reset_surface);
      
      SDL_Surface* back_surface = TTF_RenderText_Solid(this->font, "Press 'g' to back to the start screen", this->text_color);
      SDL_Texture* back_texture = SDL_CreateTextureFromSurface(render, back_surface);
      SDL_Rect back_shape = SDL_Rect{(WIDTH/2)-(back_surface->w/2), (HEIGHT/2)+(back_surface->h)+50, back_surface->w, back_surface->h};
      SDL_FreeSurface(back_surface);

      SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
      SDL_RenderCopy(render, game_over_texture, NULL, &game_over_shape);
      SDL_RenderCopy(render, reset_texture, NULL, &reset_shape);
      SDL_RenderCopy(render, back_texture, NULL, &back_shape);
      SDL_DestroyTexture(game_over_texture); 
      SDL_DestroyTexture(back_texture); 
      SDL_DestroyTexture(reset_texture); 
      return;
    }
    this->board.update_player_pos();
    uint8_t** board = this->board.get_board();
    for(size_t i = 0; i < this->board_h; i++)
      for(size_t j = 0; j < this->board_w; j++){
        SDL_Rect rect = SDL_Rect{(int)((j*SQUARE_SIDE)+this->left_padding), (int)i*SQUARE_SIDE, SQUARE_SIDE, SQUARE_SIDE};
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
    if(this->score_texture != nullptr)
      SDL_DestroyTexture(this->score_texture);
    SDL_Surface* score_surface = TTF_RenderText_Solid(this->font, to_string(this->player->get_score()).c_str(), this->text_color);
    this->score_texture = SDL_CreateTextureFromSurface(render, score_surface);
    this->score_shape = SDL_Rect{20, 60, score_surface->w, score_surface->h};
    SDL_FreeSurface(score_surface);

    SDL_RenderCopy(render, this->score_texture, NULL, &this->score_shape);
  } 
  
  void PlayerScreen::close_event(){}
 
  void PlayerScreen::reset(){
    this->finished_game = false;
    delete this->player;
    this->player = new Player{this->score_step, this->board_w, this->board_h};
    this->board.add_player(this->player);
    this->board.random_food(); 
  }

  PlayerScreen::~PlayerScreen(){
    SDL_DestroyTexture(this->score_texture);
    SDL_DestroyTexture(this->score_text_texture);
    delete this->player;
  }
}
