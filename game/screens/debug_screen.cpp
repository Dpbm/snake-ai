#include <iostream>
#include <cmath>
#include <vector>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include "debug_screen.h"
#include "screens.h"
#include "../../helpers/constants.h"
#include "../../helpers/utils.h"

using std::cos;
using std::sin;
using std::abs;
using std::cout;
using std::endl;
using std::vector;
using Screens::Screen;
// using Utils::vec2;

namespace GameDebugScreen{

  DebugScreen::DebugScreen(SDL_Renderer* render){
    this->player->direction_right();
  };

  void DebugScreen::execute(SDL_Renderer* render, bool& game_loop){
    vector<int> sensors; 
SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
    
    // vector<vec2> food_points;
    // SDL_SetRenderDrawColor(render, 255, 255, 0, 255);
    // for(size_t i = 0; i < 360; i+=5){
    //   vec2 position{
    //     (int)(this->food.get_x() + (cos((PI*i)/180)*WIDTH)),
    //     (int)(this->food.get_y() - (sin((PI*i)/180)*HEIGHT))
    //   };
    //   

    //   food_points.push_back(position); 
    //   SDL_RenderDrawLine(render, 
    //                      this->food.get_x(),
    //                      this->food.get_y(), 
    //                      position.x, position.y);
    // }

  //   vector<vec2> points;
  //   int px = this->player->get_x(); 
  //   int py = this->player->get_y(); 

  //   if(player->get_mov_x() == 1){
  //     for(size_t i = 0; i <= 90 ; i+=10){
  //       vec2 position{
  //         (int)(px + (cos((PI*i)/180)*(WIDTH-px))),
  //         (int)(py - (sin((PI*i)/180)*py))
  //       };
  //       points.push_back(position); 
  //     }
  //     for(int i = 0; i >= -90 ; i-=10){
  //       vec2 position{
  //         (int)(px + (cos((PI*i)/180)*(WIDTH-px))),
  //         (int)(py - (sin((PI*i)/180)*(HEIGHT-py)))
  //       };
  //       
  //       points.push_back(position); 
  //     }
  //   }



  //   for(vec2 point: points){
  //       SDL_SetRenderDrawColor(render, 255, 0, 255, 255);
  //       SDL_RenderDrawLine(render, 
  //                          this->player->get_x(),
  //                          this->player->get_y(), 
  //                          point.x, point.y);
  //   }

  // 
  //
  
    int px  = this->player->get_x();
    int py  = this->player->get_y();
    int fx  = this->food.get_x();
    int fy  = this->food.get_y();

    SDL_SetRenderDrawColor(render, 255, 0, 255, 255);
    double hip = sqrt(pow(fx-px,2) + pow(py-fy,2));
    double angle = acos(abs(fx-px)/hip); 
    if(fx > px && fy < py){
      SDL_RenderDrawLine(render,
                         px, 
                         py, 
                         px+abs(fx-px), 
                         py);
      SDL_RenderDrawLine(render,
                         px+abs(fx-px), 
                         py, 
                         px+abs(fx-px), 
                         py-(abs(py-fy)));
    }else if(fx > px && fy > py){
      SDL_RenderDrawLine(render,
                         px, 
                         py, 
                         px+abs(fx-px), 
                         py);
      SDL_RenderDrawLine(render,
                         px+abs(fx-px), 
                         py, 
                         px+abs(fx-px), 
                         py+(abs(fy-py)));
      angle += (3*PI)/2;
    }else if(fx < px && fy < py){
      SDL_RenderDrawLine(render,
                         px, 
                         py, 
                         px-abs(px-fx), 
                         py);
      SDL_RenderDrawLine(render,
                         px-abs(px-fx), 
                         py, 
                         px-abs(px-fx), 
                         py-(abs(py-fy)));
      angle += PI/2;
    
    }else if(fx < px && fy > py){
      SDL_RenderDrawLine(render,
                         px, 
                         py, 
                         px-abs(px-fx), 
                         py);
      SDL_RenderDrawLine(render,
                         px-abs(px-fx), 
                         py, 
                         px-abs(px-fx), 
                         py+(abs(py-fy)));
      angle += PI;
    }

    SDL_RenderDrawLine(render, px, py, fx, fy);
    cout << (180*angle)/PI << endl; 
    this->player->render(render);
    this->food.render(render);
  };

  Screen* DebugScreen::key_event(const SDL_Keycode& key){
    switch (key) {
      case SDLK_w:
        this->player->direction_up();
        this->player->update_position();
        break;

      case SDLK_s:
        this->player->direction_down();
        this->player->update_position();
        break;

      case SDLK_d:
        this->player->direction_right();
        this->player->update_position();
        break;

      case SDLK_a:
        this->player->direction_left();
        this->player->update_position();
        break;

      default: break;
    }
    return nullptr;
  };
  
  DebugScreen::~DebugScreen(){
    delete this->player;
  };


};

