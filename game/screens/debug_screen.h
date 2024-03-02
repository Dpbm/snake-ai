#pragma once

#include "./screens.h"
#include "../player.h"
#include "../food.h"
#include "ai_screen.h"
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>

using Screens::Screen;
using Players::Player;
using Foods::Food;

namespace GameDebugScreen {
  class DebugScreen : public Screen{
    public:
      DebugScreen(SDL_Renderer* render);
      void execute(SDL_Renderer* render, bool& game_loop);
      Screen* key_event(const SDL_Keycode& key);
      ~DebugScreen();
    private:
      Player* player = new Player(1, 100);
      Food food;
  };
};
