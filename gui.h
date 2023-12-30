#ifndef GUI_
#define GUI_

#include <SDL2/SDL.h>
#include <iostream>
#include "food.h"
#include "player.h"

namespace GUI {
  class Game{
    public:
      Game(char* title, int width, int height);
      ~Game();
      bool event_close();
      void render_food();
      void render_player();
      void clear_screen();
      void show();
      SDL_Event *get_event();
      Players::Player* get_player();


    private:
      int width, height;
      SDL_Window *window;
      SDL_Renderer *render;
      Foods::Food *food = new Foods::Food();
      Players::Player *player = new Players::Player();
  };
}

#endif // !GUI_
