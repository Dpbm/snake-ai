#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include "screens.h"

namespace Screens{
  Screen::Screen(SDL_Renderer* render){
    this->render = render;
  }

  void Screen::execute(bool& game_loop){}
  
  Screen* Screen::key_event(const SDL_Keycode& key){
    return nullptr;
  }
  
  Screen::~Screen(){}

  void Screen::close_event(){}
};
