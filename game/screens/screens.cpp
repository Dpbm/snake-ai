#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <cstdint>
#include "screens.h"
#include "../board.h"
#include "../../helpers/constants.h"

using Game::Board;

namespace Screens{
  Screen::Screen(SDL_Renderer* render){
    this->render = render;
  }

  void Screen::execute(bool& game_loop){}
  
  Screen* Screen::key_event(const SDL_Keycode& key){
    return nullptr;
  }
  
  void Screen::close_event(){}
  
  void Screen::render_board(Board *board){
    uint8_t** board_m = board->get_board();
    uint16_t board_h = board->get_height();
    uint16_t board_w = board->get_width();

    for(size_t i = 0; i < board_h; i++)
      for(size_t j = 0; j < board_w; j++){
        SDL_Rect rect = SDL_Rect{(int)((j*SQUARE_SIDE)+this->left_padding), (int)i*SQUARE_SIDE, SQUARE_SIDE, SQUARE_SIDE};
        switch(board_m[i][j]){
          case 0: {
            SDL_SetRenderDrawColor(this->render, 100, 100, 100, 255);
            SDL_RenderDrawRect(this->render, &rect);
            break;
          }
          
          case 1: {
            SDL_SetRenderDrawColor(this->render, 0, 0, 255, 255);
            SDL_RenderFillRect(this->render, &rect);
            break;
          }
        
          case 2: {
            SDL_SetRenderDrawColor(this->render, 0, 255, 0, 255);
            SDL_RenderFillRect(this->render, &rect);
            break;
          }

          default: break;
        }
      }
  }
  

  Screen::~Screen(){}
};
