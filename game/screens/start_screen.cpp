#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <cstdlib>
#include "../../helpers/constants.h"
#include "start_screen.h"
#include "ai_screen_play.h"
#include "player_screen.h"
#include "ai_screen.h"

using std::exit;
using std::cout;
using std::endl;

namespace Screens {  
  StartScreen::StartScreen(SDL_Renderer* render) : Screen(render){
    if(!this->font){
      cout << "Failed on getting font!" << endl;
      cout << TTF_GetError() << endl;
      exit(1);
    }
    SDL_Surface* title_surface = TTF_RenderText_Solid(this->font, "SNAKE GAME AI", this->text_color);
    SDL_Surface* ai_surface = TTF_RenderText_Solid(this->font, "PRESS 'A' TO TRAIN THE AI", this->text_color);
    SDL_Surface* ai_play_surface = TTF_RenderText_Solid(this->font, "PRESS 'S' TO AI PLAY", this->text_color);
    SDL_Surface* player_surface = TTF_RenderText_Solid(this->font, "PRESS 'D' TO PLAY", this->text_color);
    SDL_Surface* qubo_surface = TTF_RenderText_Solid(this->font, "PRESS 'Q' TO QUBO PLAY", this->text_color);
    
    this->title_texture = SDL_CreateTextureFromSurface(render, title_surface);
    this->ai_texture = SDL_CreateTextureFromSurface(render, ai_surface);
    this->ai_play_texture = SDL_CreateTextureFromSurface(render, ai_play_surface);
    this->player_texture = SDL_CreateTextureFromSurface(render, player_surface);
    this->qubo_texture = SDL_CreateTextureFromSurface(render, qubo_surface);

    this->title_shape = SDL_Rect{(WIDTH/2) - (title_surface->w/2), 60, title_surface->w, title_surface->h};
    this->ai_shape = SDL_Rect{(WIDTH/2) - (ai_surface->w/2), 240, ai_surface->w, ai_surface->h};
    this->ai_play_shape = SDL_Rect{(WIDTH/2) - (ai_play_surface->w/2), this->ai_shape.y+this->ai_shape.h+20, ai_play_surface->w, ai_play_surface->h};
    this->player_shape = SDL_Rect{(WIDTH/2) - (player_surface->w/2), this->ai_play_shape.y+this->ai_play_shape.h+20, player_surface->w, player_surface->h};
    this->qubo_shape = SDL_Rect{(WIDTH/2) - (qubo_surface->w/2), this->player_shape.y+this->player_shape.h+20, qubo_surface->w, qubo_surface->h};
    
    SDL_FreeSurface(title_surface);
    SDL_FreeSurface(ai_surface);
    SDL_FreeSurface(ai_play_surface);
    SDL_FreeSurface(player_surface);
    SDL_FreeSurface(qubo_surface);
  }

  Screen* StartScreen::key_event(const SDL_Keycode& key){
    switch (key) {
      case SDLK_a:
        return new AIScreen(this->render);
      case SDLK_s:
        return new AIPlayScreen(this->render);
      case SDLK_d:
        return new PlayerScreen(this->render);
      case SDLK_q:
        return nullptr;
      default:
        break;
    }
    return nullptr;
  }

  void StartScreen::execute(bool& game_loop){
    SDL_RenderClear(this->render);
    SDL_RenderCopy(this->render, this->title_texture, NULL, &this->title_shape);
    SDL_RenderCopy(this->render, this->ai_texture, NULL, &this->ai_shape);
    SDL_RenderCopy(this->render, this->ai_play_texture, NULL, &this->ai_play_shape);
    SDL_RenderCopy(this->render, this->player_texture, NULL, &this->player_shape);
    SDL_RenderCopy(this->render, this->qubo_texture, NULL, &this->qubo_shape);
    SDL_RenderPresent(this->render);
  }

  StartScreen::~StartScreen(){
    SDL_DestroyTexture(this->title_texture);
    SDL_DestroyTexture(this->ai_texture);
    SDL_DestroyTexture(this->ai_play_texture);
    SDL_DestroyTexture(this->player_texture);
    SDL_DestroyTexture(this->qubo_texture);
  }
};
