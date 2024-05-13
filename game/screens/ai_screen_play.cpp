#include <SDL2/SDL_timer.h>
#include <cstddef>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_stdinc.h>
#include "../../nativefiledialog-extended/src/include/nfd.h"
#include "screens.h"
#include "ai_screen_play.h"
#include "../../helpers/utils.h"

using std::cout;
using std::endl;
using std::size_t;
using Utils::parse_nn;

namespace Screens {
  AIPlayScreen::AIPlayScreen(SDL_Renderer* render) : Screen(render){
    
    if(NFD_Init() != NFD_OKAY){
      cout << "Failed on load NFD" << endl;
      exit(1);
    }

    nfdchar_t *outPath;
    nfdresult_t result = NFD_OpenDialog(&outPath, NULL, 0, NULL);

    if(result == NFD_OKAY){
      this->player = new AIPlayer(this->board_w, this->board_h, parse_nn(outPath));
      this->board.add_player(this->player);
      NFD_FreePath(outPath);
      return;
    }

    cout << "You must select a weights file!" << endl;
    exit(1);
  }

  void AIPlayScreen::execute(bool& game_loop){
    this->render_board(&this->board); 
    SDL_SetRenderDrawColor(this->render, 0, 0, 0, 255);
  }

  Screen* AIPlayScreen::key_event(const SDL_Keycode& key){
    return nullptr;
  }

  void AIPlayScreen::close_event(){
  }

  
  AIPlayScreen::~AIPlayScreen(){
    delete this->player;
    NFD_Quit();
  }
}
