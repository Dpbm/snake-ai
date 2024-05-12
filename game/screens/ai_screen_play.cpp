#include <SDL2/SDL_timer.h>
#include <cstddef>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_stdinc.h>
#include "screens.h"
#include "ai_screen_play.h"
#include "../../genetic/population.h"

using std::size_t;
using Genetic::Individual;

namespace Screens {
  AIPlayScreen::AIPlayScreen(SDL_Renderer* render) : Screen(render){
    
    
    this->player = new AIPlayer(this->board_w, this->board_h);
    this->board.add_player(this->player);
  }

  void AIPlayScreen::execute(bool& game_loop){
    this->render_board(&this->board); 
  }

  Screen* AIPlayScreen::key_event(const SDL_Keycode& key){
    return nullptr;
  }

  void AIPlayScreen::close_event(){
  }

  
  AIPlayScreen::~AIPlayScreen(){
  }
}
