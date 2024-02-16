#include <cmath>
#include <iostream>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include "ai_screen.h"
#include "../player.h"
#include "../food.h"
#include "screens.h"
#include "../../helpers/constants.h"

using std::cout;
using std::endl;
using std::abs;
using Players::Player;
using Foods::Food;
using Screens::Screen;

namespace GameAIScreen {
  Player* player;
  Food* food;
  bool debug;


  AIScreen::AIScreen(){
    //this->player->direction_right();
  }

  void AIScreen::execute(SDL_Renderer* render, bool& game_loop){
    this->player->update_position();
   
    int px = player->get_x();
    int py = player->get_y();
    int fx = food->get_x();
    int fy = food->get_y();

    int frontal_sensor = WIDTH-px;
    int back_sensor = px;
    int top_sensor = py;
    int bottom_sensor = HEIGHT-py;
    int food_sensor = sqrt(pow(px-fx, 2) + pow(py-fy,2));


    cout << "----SENSORS---" << endl;
    cout << "Frontal Sensor: " << frontal_sensor << endl; 
    cout << "Back Sensor: " << back_sensor << endl; 
    cout << "Top Sensor: " << top_sensor << endl; 
    cout << "Bottom Sensor: " << bottom_sensor << endl; 
    cout << "Food Sensor: " << food_sensor << endl << endl; 

    if(this->debug){
      SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
      SDL_RenderDrawLine(render, px, py+(PLAYER_H/2), WIDTH, py+(PLAYER_H/2));
      SDL_RenderDrawLine(render, 0, py+(PLAYER_H/2), px, py+(PLAYER_H/2));
      SDL_RenderDrawLine(render, px+(PLAYER_W/2), 0, px+(PLAYER_W/2), py);
      SDL_RenderDrawLine(render, px+(PLAYER_W/2), py, px+(PLAYER_W/2), HEIGHT);
      SDL_RenderDrawLine(render, px+(PLAYER_H/2), py+(PLAYER_W/2), food->get_x()+(FOOD_H/2), food->get_y()+(FOOD_W/2));
    }

    if(this->player->is_die()){
      cout << "GAME OVER!" << endl;
      game_loop = false;
    }

    this->food->render(render);
    this->player->render(render);
  }

  Screen* AIScreen::key_event(const SDL_Keycode& key){
    if(key == SDLK_p)
      this->debug = !this->debug;

    if(this->debug){
      switch (key) {
        case SDLK_w:
          this->player->direction_up();
          break;

        case SDLK_s:
          this->player->direction_down();
          break;

        case SDLK_d:
          this->player->direction_right();
          break;

        case SDLK_a:
          this->player->direction_left();
          break;

        default: break;
      }
    }
  
    return nullptr;
  }
  
  AIScreen::~AIScreen(){
    delete this->player;
    delete this->food;
  }
}
