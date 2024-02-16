#pragma once

#include "screens.h"
#include "../player.h"
#include "../food.h"

using Screens::Screen;
using Players::Player;
using Foods::Food;

namespace GameAIScreen{
  class AIScreen: public Screen{
    public:
      AIScreen();
      void execute(SDL_Renderer* render, bool& game_loop);
      Screen* key_event(const SDL_Keycode& key);
      ~AIScreen();
    private:
      Player* player = new Player(1, 10);
      Food* food = new Food;
      bool debug = false;
  };
};
