#ifndef GUI_
#define GUI_

#include <SDL2/SDL.h>

namespace GUI {
  class Game{
    public:
      Game(char* title, int width, int height);
      ~Game();
      bool event_close();

    private:
      int width, height;
      SDL_Window *window;
  };
}

#endif // !GUI_
