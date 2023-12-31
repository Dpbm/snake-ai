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
      void listen_event();
      Players::Player* get_player();
      bool event_move(SDL_Keycode key);
      bool event_keydown();


    private:
      int width, height;
      SDL_Window *window;
      SDL_Renderer *render;
      Foods::Food *food = new Foods::Food();
      Players::Player *player = new Players::Player();
      SDL_Event *event = new SDL_Event;
      int last_event_tick;
      void update_last_tick();
      bool passed_debounce_time();
      bool pressed_that_key(SDL_Keycode key);
  };
}

#endif // !GUI_
