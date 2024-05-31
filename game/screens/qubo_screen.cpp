#include <SDL2/SDL_timer.h>
#include <cstddef>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_stdinc.h>
#include <string>
#include "../../helpers/constants.h"
#include "qubo_screen.h"
#include "start_screen.h"

using std::to_string;
using std::cout;
using std::endl;
using std::size_t;

namespace Screens {
  QuboScreen::QuboScreen(SDL_Renderer* render) : Screen(render){
    if(!this->font){
      cout << "Failed on getting font!" << TTF_GetError() << endl;
      exit(1);
    }

    SDL_Surface* score_text_surface = TTF_RenderText_Solid(this->font, "QUBO Score", this->text_color);
    this->score_text_texture = SDL_CreateTextureFromSurface(render, score_text_surface);
    this->score_text_shape = SDL_Rect{20, 20, score_text_surface->w, score_text_surface->h};
    SDL_FreeSurface(score_text_surface);

    if(this->score_text_texture == nullptr){
      cout << "Failed on creating score text texture!" << SDL_GetError() << endl;
      exit(1);
    }
    this->board.add_player(this->player);
    this->left_padding = 10 * SQUARE_SIDE;
  }

  void QuboScreen::execute(bool& game_loop){
    bool won = this->player->get_score() >= this->max_score; 
    this->finished_game = won || this->player->is_dead();
    if(this->finished_game){
      SDL_Surface* game_over_surface = TTF_RenderText_Solid(this->title_font, won ? "QUBO Wins!!!" : "Game Over", this->text_color);
      SDL_Texture* game_over_texture = SDL_CreateTextureFromSurface(this->render, game_over_surface);
      SDL_Rect game_over_shape = SDL_Rect{(WIDTH/2)-(game_over_surface->w/2), (HEIGHT/2)-(game_over_surface->h), game_over_surface->w, game_over_surface->h};
      SDL_FreeSurface(game_over_surface);
      
      SDL_Surface* reset_surface = TTF_RenderText_Solid(this->font, "Press 'r' to reset", this->text_color);
      SDL_Texture* reset_texture = SDL_CreateTextureFromSurface(this->render, reset_surface);
      SDL_Rect reset_shape = SDL_Rect{(WIDTH/2)-(reset_surface->w/2), (HEIGHT/2)+(reset_surface->h)+20, reset_surface->w, reset_surface->h};
      SDL_FreeSurface(reset_surface);
      
      SDL_Surface* back_surface = TTF_RenderText_Solid(this->font, "Press 'g' to back to the start screen", this->text_color);
      SDL_Texture* back_texture = SDL_CreateTextureFromSurface(this->render, back_surface);
      SDL_Rect back_shape = SDL_Rect{(WIDTH/2)-(back_surface->w/2), (HEIGHT/2)+(back_surface->h)+50, back_surface->w, back_surface->h};
      SDL_FreeSurface(back_surface);

      SDL_SetRenderDrawColor(this->render, 0, 0, 0, 255);
      SDL_RenderCopy(this->render, game_over_texture, NULL, &game_over_shape);
      SDL_RenderCopy(this->render, reset_texture, NULL, &reset_shape);
      SDL_RenderCopy(this->render, back_texture, NULL, &back_shape);
      SDL_DestroyTexture(game_over_texture); 
      SDL_DestroyTexture(back_texture); 
      SDL_DestroyTexture(reset_texture); 
      return;
    }
    this->player->next_mov(this->board.get_food()); 
    this->board.update_player_pos();
    this->render_board(&this->board); 
   
    SDL_SetRenderDrawColor(this->render, 0, 0, 0, 255);
    SDL_RenderCopy(this->render, this->score_text_texture, NULL, &this->score_text_shape);
  
    if(this->score_texture != nullptr)
      SDL_DestroyTexture(this->score_texture);
    SDL_Surface* score_surface = TTF_RenderText_Solid(this->font, to_string(this->player->get_score()).c_str(), this->text_color);
    this->score_texture = SDL_CreateTextureFromSurface(this->render, score_surface);
    this->score_shape = SDL_Rect{20, 60, score_surface->w, score_surface->h};
    SDL_FreeSurface(score_surface);

    SDL_RenderCopy(this->render, this->score_texture, NULL, &this->score_shape);
  }

  Screen* QuboScreen::key_event(const SDL_Keycode& key){
    switch (key) {
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

  void QuboScreen::close_event(){
  }

  void QuboScreen::reset(){
    this->finished_game = false;
    delete this->player;
    this->player = new QuboPlayer(this->board_w, this->board_h);
    this->board.add_player(this->player);
    this->board.random_food(); 
  }
  
  QuboScreen::~QuboScreen(){
    delete this->player;
    SDL_DestroyTexture(this->score_texture);
    SDL_DestroyTexture(this->score_text_texture);
  }
}
