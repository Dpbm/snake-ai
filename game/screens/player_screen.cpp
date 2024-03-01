#include <SDL2/SDL_surface.h>
#include <iostream>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include "player_screen.h"
#include "screens.h"
#include "../player.h"

using std::to_string;
using std::cout;
using std::endl;
using Screens::Screen;
using Players::Player;


namespace GamePlayerScreen{
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
  }

  Screen* PlayerScreen::key_event(const SDL_Keycode& key){
    switch (key) {
      case SDLK_w:
        this->player->direction_up();
        break;

      case SDLK_s:
        this->player->direction_down();
        break;

      case SDLK_d:
        this->player->direction_right();
        break;

      case SDLK_a:
        this->player->direction_left();
        break;

      default: break;
    }
    return nullptr;
  }

  void PlayerScreen::execute(SDL_Renderer* render, bool& game_loop){
    this->player->update_position();

    if(this->player->is_die()){
      cout << "GAME OVER!" << endl;
      game_loop = false;
      return;
    }else if(this->player->get_score() >= this->max_score){
      cout << "WON!" << endl;
      game_loop = false;
      return;
    }
    
    if(this->player->collision(this->food.get_x(), this->food.get_y())){
      this->food.update_position();
      this->player->update_score();
      unsigned int player_score = this->player->get_score();

      SDL_Surface* score_surface = TTF_RenderText_Solid(this->font, to_string(player_score).c_str(), this->text_color);
      SDL_DestroyTexture(this->score_texture);
      this->score_texture = SDL_CreateTextureFromSurface(render, score_surface);
      this->score_shape.w = score_surface->w;
      SDL_FreeSurface(score_surface);
      
      if(this->score_texture == nullptr){
        cout << "Failed on recreating score texture!" << SDL_GetError() << endl;
        exit(1);
      }
      cout << "Player score: " << player_score << endl;
    }

    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    SDL_RenderFillRect(render, &this->screen_separator);
    SDL_RenderCopy(render, this->score_text_texture, NULL, &this->score_text_shape);
    SDL_RenderCopy(render, this->score_texture, NULL, &this->score_shape);
    this->food.render(render);
    this->player->render(render);
  } 
  
  PlayerScreen::~PlayerScreen(){
    SDL_DestroyTexture(this->score_texture);
    SDL_DestroyTexture(this->score_text_texture);
    delete this->player;
  }
}
