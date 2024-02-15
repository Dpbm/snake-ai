#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <cstdlib>
#include "start_screen.h"
#include "../../helpers/constants.h"
#include "player_screen.h"

using std::exit;
using std::cout;
using std::endl;
using GamePlayerScreen::PlayerScreen;

namespace GameStartScreen {  
  TTF_Font* font;
  SDL_Color* text_color;
  SDL_Texture* title_texture;
  SDL_Texture* ai_texture;
  SDL_Texture* player_texture;
  SDL_Rect* title_shape;
  SDL_Rect* ai_shape;
  SDL_Rect* player_shape;
 
  StartScreen::StartScreen(SDL_Renderer* render){
    if(!this->font){
      cout << "Failed on getting font!" << endl;
      cout << TTF_GetError() << endl;
      exit(1);
    }
    SDL_Surface* title_surface = TTF_RenderText_Solid(this->font, "SNAKE GAME AI", *this->text_color);
    SDL_Surface* ai_surface = TTF_RenderText_Solid(this->font, "PRESS 'A' FOR AI", *this->text_color);
    SDL_Surface* player_surface = TTF_RenderText_Solid(this->font, "PRESS 'D' TO PLAY", *this->text_color);
    
    this->title_texture = SDL_CreateTextureFromSurface(render, title_surface);
    this->ai_texture = SDL_CreateTextureFromSurface(render, ai_surface);
    this->player_texture = SDL_CreateTextureFromSurface(render, player_surface);

    int title_surface_width = title_surface->w; 
    int title_surface_height = title_surface->h; 

    int ai_surface_width = ai_surface->w; 
    int ai_surface_height = ai_surface->h; 
    
    int player_surface_width = player_surface->w; 
    int player_surface_height = player_surface->h; 
    
    SDL_FreeSurface(title_surface);
    SDL_FreeSurface(ai_surface);
    SDL_FreeSurface(player_surface);

    this->title_shape->x = (WIDTH/2) - (title_surface_width/2);
    this->title_shape->y = 60;
    this->title_shape->h = title_surface_height;
    this->title_shape->w = title_surface_width;

    this->ai_shape->x = (WIDTH/2) - (ai_surface_width/2);
    this->ai_shape->y = 240;
    this->ai_shape->h = ai_surface_height;
    this->ai_shape->w = ai_surface_width;
  
    this->player_shape->x = (WIDTH/2) - (player_surface_width/2);
    this->player_shape->y = this->ai_shape->y + this->ai_shape->h + 20;
    this->player_shape->h = player_surface_height;
    this->player_shape->w = player_surface_width;
  }

  Screen* StartScreen::key_event(const SDL_Keycode& key){
    switch (key) {
      case SDLK_a:
        break; //TODO: add a pointer to functions, and here this set the pointer to the function of ai
      case SDLK_d:
        return new PlayerScreen;
      default:
        break;
    }
    return nullptr;
  }

  void StartScreen::execute(SDL_Renderer* render, bool& game_loop){
    SDL_RenderClear(render);
    SDL_RenderCopy(render, this->title_texture, NULL, this->title_shape);
    SDL_RenderCopy(render, this->ai_texture, NULL, this->ai_shape);
    SDL_RenderCopy(render, this->player_texture, NULL, this->player_shape);
    SDL_RenderPresent(render);
  }

  StartScreen::~StartScreen(){
    SDL_DestroyTexture(this->title_texture);
    SDL_DestroyTexture(this->ai_texture);
    SDL_DestroyTexture(this->player_texture);
    delete this->title_shape;
    delete this->ai_shape;
    delete this->player_shape;
    delete this->text_color;
  }
};
