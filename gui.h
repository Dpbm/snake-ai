#ifndef GUI_
#define GUI_

#include <SDL2/SDL.h>
#include <iostream>
#include "player.h"

namespace GUI {
  class Game{
    public:
      Game(char* title, int width, int height);
      ~Game();
      bool event_close();
      void draw_food();
      void set_food_pos();
      void set_food_pos(unsigned int x, unsigned int y);
      void render_player();
      void clear_screen();
      void show();
      SDL_Event get_event();
      Players::Player* get_player();


    private:
      int width, height;
      SDL_Window *window;
      SDL_Renderer *render;
      unsigned int food_x, food_y;
      Players::Player *player = new Players::Player();
  };
}

#endif // !GUI_
