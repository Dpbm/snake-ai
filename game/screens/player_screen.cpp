#include <SDL2/SDL_surface.h>
#include <iostream>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include "player_screen.h"
#include "screens.h"
#include "../player.h"
#include "../food.h"

using std::to_string;
using std::cout;
using std::endl;
using Screens::Screen;
using Players::Player;
using Foods::Food;


namespace GamePlayerScreen{
  TTF_Font* font;
  SDL_Color* text_color;
  Player* player; 
  Food* food;
  unsigned int max_score;
  SDL_Rect* score_text_shape;
  SDL_Rect* score_shape;
  SDL_Texture* score_text_texture;
  SDL_Texture* score_texture;

  PlayerScreen::PlayerScreen(SDL_Renderer* render){
    if(!this->font){
      cout << "Failed on getting font!" << endl;
      cout << TTF_GetError() << endl;
      exit(1);
    }
    SDL_Surface* score_text_surface = TTF_RenderText_Solid(this->font, "Score ", *this->text_color);
    this->score_text_texture = SDL_CreateTextureFromSurface(render, score_text_surface);
    this->score_text_shape->x = 20;
    this->score_text_shape->y = 20;
    this->score_text_shape->h = score_text_surface->h;
    this->score_text_shape->w = score_text_surface->w;
    
    SDL_Surface* score_surface = TTF_RenderText_Solid(this->font, "0", *this->text_color);
    this->score_texture = SDL_CreateTextureFromSurface(render, score_surface);
    this->score_shape->x = score_text_shape->w + 20;
    this->score_shape->y = 20;
    this->score_shape->h = score_surface->h;
    this->score_shape->w = score_surface->w;
    
    SDL_FreeSurface(score_text_surface);
    SDL_FreeSurface(score_surface);
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
    
    if(this->player->collision(this->food->get_x(), this->food->get_y())){
      this->food->update_position();
      this->player->update_score();
      unsigned int player_score = this->player->get_score();

      SDL_Surface* score_surface = TTF_RenderText_Solid(this->font, to_string(player_score).c_str(), *this->text_color);
      SDL_DestroyTexture(this->score_texture);
      this->score_texture = SDL_CreateTextureFromSurface(render, score_surface);
      this->score_shape->h = score_surface->h;
      this->score_shape->w = score_surface->w;
      SDL_FreeSurface(score_surface);
      cout << "Player score: " << player_score << endl;
    }

    SDL_RenderCopy(render, this->score_text_texture, NULL, this->score_text_shape);
    SDL_RenderCopy(render, this->score_texture, NULL, this->score_shape);
    this->food->render(render);
    this->player->render(render);
  } 
  
  PlayerScreen::~PlayerScreen(){
    SDL_DestroyTexture(this->score_texture);
    SDL_DestroyTexture(this->score_text_texture);
    delete this->food;
    delete this->player;
    delete this->text_color;
    delete this->score_text_shape;
    delete this->score_shape;
  }
}