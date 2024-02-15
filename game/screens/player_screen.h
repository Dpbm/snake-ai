#pragma once

#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include "screens.h"
#include "../food.h"
#include "../player.h"

using Screens::Screen;
using Foods::Food;
using Players::Player;

namespace GamePlayerScreen{

  class PlayerScreen : public Screen{
    public:
      void execute(SDL_Renderer* render, bool& game_loop);
      Screen* key_event(const SDL_Keycode& key);
      ~PlayerScreen();
    private:
      Food* food = new Food;
      unsigned int max_score = 1000;
      Player* player = new Player(10, max_score);
  };
};
