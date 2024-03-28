#pragma once

#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include "screens.h"
#include "../food.h"
#include "../players/player.h"

using Screens::Screen;
using Foods::Food;
using Players::Player;

namespace GamePlayerScreen{

  class PlayerScreen : public Screen{
    public:
      PlayerScreen(SDL_Renderer* render);
      void execute(SDL_Renderer* render, bool& game_loop);
      Screen* key_event(const SDL_Keycode& key);
      ~PlayerScreen();
      void close_event();
    private:
      Food food;
      unsigned int max_score = 1000;
      Player* player = new Player(10, max_score);
      TTF_Font* font = TTF_OpenFont("./assets/pressstart.ttf", 20);
      SDL_Color text_color{ 255, 255, 255 };
      SDL_Rect score_text_shape;
      SDL_Rect score_shape;
      SDL_Rect screen_separator{LEFT_WALL, 0, 1, HEIGHT};
      SDL_Texture* score_text_texture;
      SDL_Texture* score_texture;
  };
};
