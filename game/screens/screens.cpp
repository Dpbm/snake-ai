#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include "screens.h"

namespace Screens{
  void Screen::execute(SDL_Renderer* render, bool& game_loop){};
  
  Screen* Screen::key_event(const SDL_Keycode& key){
    return nullptr;
  };
  
  Screen::~Screen(){};
  
};
