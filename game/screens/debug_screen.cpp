#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include "debug_screen.h"
#include "screens.h"
#include "../../helpers/constants.h"
#include "../../helpers/utils.h"
#include "../../machine/activation.h"
#include "../../matrix/matrix.h"

using std::size_t;
using std::cos;
using std::sin;
using std::abs;
using std::cout;
using std::endl;
using std::vector;
using Screens::Screen;
using Matrices::Matrix;
// using Utils::vec2;

namespace GameDebugScreen{

  DebugScreen::DebugScreen(SDL_Renderer* render){
    this->nn->add_layer(this->input_layer);
    this->nn->add_layer(4);
    this->nn->add_layer(4);
    
    this->nn->get_layer(1)->set_activation_function(Activations::tanh);
    this->nn->get_layer(2)->set_activation_function(Activations::softmax);
    this->input_layer->set_values(this->input_data);
    this->player->direction_right();
    this->reset_weights();
};
 
  void DebugScreen::reset_weights(){
    for(size_t n = 0; n < 2; n++){
      Matrix* w = this->nn->get_weight(n)->get_weights();

      for(size_t i = 0; i < w->get_height(); i++)
        for(size_t j =0; j < w->get_width(); j++)
          w->update_value(i, j, Utils::random(-1,1));
    }
  }

  void DebugScreen::update_input_data(uint16_t px, uint16_t py, uint16_t fx, uint16_t fy){
    double hip = sqrt(pow(fx-px,2) + pow(py-fy,2));
    double angle = hip == 0 ? 0 : acos(abs(fx-px)/hip); 

    if(fx > px && fy > py)
      angle += (3*PI)/2;
    else if(fx < px && fy < py)
      angle += PI/2;
    else if(fx < px && fy > py)
      angle += PI;
    else if(fy == py && px < fx)
      angle = 0;
    else if(fy == py && px < fx)
      angle = PI;
    else if(px == fx && py > fy)
      angle = PI/2;
    else if(px == fx && py < fy)
      angle = (3*PI)/2;
    
    
    this->input_data->update_value(0, 0, 1-((fx-px)/1000.0));
    this->input_data->update_value(0, 1, 1-((fy-py)/1000.0));
    this->input_data->update_value(0, 2, 1);
  }

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

    // SDL_SetRenderDrawColor(render, 255, 0, 255, 255);
    // double hip = sqrt(pow(fx-px,2) + pow(py-fy,2));
    // double angle = acos(abs(fx-px)/hip); 
    // if(fx > px && fy < py){
    //   SDL_RenderDrawLine(render,
    //                      px, 
    //                      py, 
    //                      px+abs(fx-px), 
    //                      py);
    //   SDL_RenderDrawLine(render,
    //                      px+abs(fx-px), 
    //                      py, 
    //                      px+abs(fx-px), 
    //                      py-(abs(py-fy)));
    // }else if(fx > px && fy > py){
    //   SDL_RenderDrawLine(render,
    //                      px, 
    //                      py, 
    //                      px+abs(fx-px), 
    //                      py);
    //   SDL_RenderDrawLine(render,
    //                      px+abs(fx-px), 
    //                      py, 
    //                      px+abs(fx-px), 
    //                      py+(abs(fy-py)));
    //   angle += (3*PI)/2;
    // }else if(fx < px && fy < py){
    //   SDL_RenderDrawLine(render,
    //                      px, 
    //                      py, 
    //                      px-abs(px-fx), 
    //                      py);
    //   SDL_RenderDrawLine(render,
    //                      px-abs(px-fx), 
    //                      py, 
    //                      px-abs(px-fx), 
    //                      py-(abs(py-fy)));
    //   angle += PI/2;
    // 
    // }else if(fx < px && fy > py){
    //   SDL_RenderDrawLine(render,
    //                      px, 
    //                      py, 
    //                      px-abs(px-fx), 
    //                      py);
    //   SDL_RenderDrawLine(render,
    //                      px-abs(px-fx), 
    //                      py, 
    //                      px-abs(px-fx), 
    //                      py+(abs(py-fy)));
    //   angle += PI;
    // }

    // SDL_RenderDrawLine(render, px, py, fx, fy);
    // cout << (180*angle)/PI << endl; 
    // cout << 1-(abs((fx - px)/(double)PLAY_WIDTH)) << endl;
    this->player->render(render);
    this->food.render(render);
  };

  Screen* DebugScreen::key_event(const SDL_Keycode& key){
    switch (key) {
      case SDLK_w:
        this->player->direction_up();
        this->player->update_position();
        this->update_input_data(this->player->get_x(), this->player->get_y(), this->food.get_x(), this->food.get_y());
        this->update_player_direction();
        break;

      case SDLK_s:
        this->player->direction_down();
        this->player->update_position();
        this->update_input_data(this->player->get_x(), this->player->get_y(), this->food.get_x(), this->food.get_y());
        this->update_player_direction();
        break;

      case SDLK_d:
        this->player->direction_right();
        this->player->update_position();
        this->update_input_data(this->player->get_x(), this->player->get_y(), this->food.get_x(), this->food.get_y());
        this->update_player_direction();
        break;

      case SDLK_a:
        this->player->direction_left();
        this->player->update_position();
        this->update_input_data(this->player->get_x(), this->player->get_y(), this->food.get_x(), this->food.get_y());
        this->update_player_direction();
        break;

      case SDLK_f:
        this->reset_weights();
        break;
    

      default: break;
    }
    return nullptr;
  };
  
  void DebugScreen::update_player_direction(){
    this->nn->feedforward();
    this->get_new_direction();
  }
  
  void DebugScreen::get_new_direction(){
    Matrix* result = this->nn->get_output_layer()->get_values();
    std::cout << "\n\n"; 
    this->nn->get_layer(0)->get_values()->show();
    this->nn->get_weight(0)->get_weights()->show();
    this->nn->get_layer(1)->get_values()->show();
    this->nn->get_weight(1)->get_weights()->show();
    result->show();
    std::cout << "\n\n"; 
    double biggest = 0;
    size_t direction = 0;
    for(size_t i = 0; i < 4; i++){
      double actual_value = result->get_position_value(0, i);
      if(actual_value > biggest){
        biggest = actual_value;
        direction = i;
      }
    }
  }
  
  DebugScreen::~DebugScreen(){
    delete this->player;
    delete this->nn;
  };


};

