#pragma once

#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include "screens.h"

namespace Screens {
  class StartScreen : public Screen{
    public:
      StartScreen(SDL_Renderer* render);
      ~StartScreen();
      void execute(bool& game_loop);
      Screen* key_event(const SDL_Keycode& key);
    
    private:
      TTF_Font* font = TTF_OpenFont("./assets/pressstart.ttf", 35);
      
      SDL_Texture* title_texture;
      SDL_Texture* ai_texture;
      SDL_Texture* player_texture;
      SDL_Texture* ai_play_texture;
      SDL_Texture* qubo_texture;

      SDL_Rect title_shape;
      SDL_Rect ai_shape;
      SDL_Rect player_shape;
      SDL_Rect ai_play_shape;
      SDL_Rect qubo_shape;
  };

};
