#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <cstdlib>
#include "start_screen.h"
#include "../../helpers/constants.h"
#include "player_screen.h"
#include "ai_screen.h"

using std::exit;
using std::cout;
using std::endl;
using GamePlayerScreen::PlayerScreen;
using GameAIScreen::AIScreen;

namespace GameStartScreen {  
  StartScreen::StartScreen(SDL_Renderer* render){
    this->render = render;
    if(!this->font){
      cout << "Failed on getting font!" << endl;
      cout << TTF_GetError() << endl;
      exit(1);
    }
    SDL_Surface* title_surface = TTF_RenderText_Solid(this->font, "SNAKE GAME AI", this->text_color);
    SDL_Surface* ai_surface = TTF_RenderText_Solid(this->font, "PRESS 'A' TO TRAIN THE AI", this->text_color);
    SDL_Surface* player_surface = TTF_RenderText_Solid(this->font, "PRESS 'D' TO PLAY", this->text_color);
    
    this->title_texture = SDL_CreateTextureFromSurface(render, title_surface);
    this->ai_texture = SDL_CreateTextureFromSurface(render, ai_surface);
    this->player_texture = SDL_CreateTextureFromSurface(render, player_surface);

    this->title_shape = SDL_Rect{(WIDTH/2) - (title_surface->w/2), 60, title_surface->w, title_surface->h};
    this->ai_shape = SDL_Rect{(WIDTH/2) - (ai_surface->w/2), 240, ai_surface->w, ai_surface->h};
    this->player_shape = SDL_Rect{(WIDTH/2) - (player_surface->w/2), this->ai_shape.y+this->ai_shape.h+20, player_surface->w, player_surface->h};
    
    SDL_FreeSurface(title_surface);
    SDL_FreeSurface(ai_surface);
    SDL_FreeSurface(player_surface);
  }

  Screen* StartScreen::key_event(const SDL_Keycode& key){
    switch (key) {
      case SDLK_a:
        return new AIScreen(this->render);
      case SDLK_d:
        return new PlayerScreen(this->render);
      default:
        break;
    }
    return nullptr;
  }

  void StartScreen::execute(SDL_Renderer* render, bool& game_loop){
    SDL_RenderClear(render);
    SDL_RenderCopy(render, this->title_texture, NULL, &this->title_shape);
    SDL_RenderCopy(render, this->ai_texture, NULL, &this->ai_shape);
    SDL_RenderCopy(render, this->player_texture, NULL, &this->player_shape);
    SDL_RenderPresent(render);
  }

  StartScreen::~StartScreen(){
    SDL_DestroyTexture(this->title_texture);
    SDL_DestroyTexture(this->ai_texture);
    SDL_DestroyTexture(this->player_texture);
  }
};
