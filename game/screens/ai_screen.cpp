#include <cmath>
#include <iostream>
#include <string>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_surface.h>
#include "ai_screen.h"
#include "../player.h"
#include "../food.h"
#include "screens.h"
#include "../../helpers/constants.h"
#include "../../helpers/utils.h"
#include "../../machine/machine.h"
#include "../../machine/layer.h"
#include "../../machine/activation.h"
#include "../../matrix/matrix.h"
#include "../../genetic/chromosome.h"
#include "../../genetic/gene.h"

using std::to_string;
using std::cout;
using std::endl;
using std::sqrt;
using std::pow;
using Players::Player;
using Foods::Food;
using Screens::Screen;
using Utils::random_int;
using Machine::NN;
using Layers::Layer;
using Activations::relu;
using Activations::sigmoid;
using Matrices::Matrix;
using Chromosomes::Chromosome;
using Genes::Gene;

namespace GameAIScreen {
  Player* player;
  Food* food;
  bool debug;
  unsigned int max_score;
  NN* nn;
  Layer* input_layer;
  Matrix<double>* input_data;
  Chromosome* chromosome;
  SDL_Rect* score_text_shape;
  SDL_Rect* score_shape;
  SDL_Texture* score_text_texture;
  SDL_Texture* score_texture;

  AIScreen::AIScreen(SDL_Renderer* render){
    if(!this->font){
      cout << "Failed on getting font!" << endl;
      cout << TTF_GetError() << endl;
      exit(1);
    }
    SDL_Surface* score_text_surface = TTF_RenderText_Solid(this->font, "AI Score ", *this->text_color);
    this->score_text_texture = SDL_CreateTextureFromSurface(render, score_text_surface);
    this->score_text_shape->x = 20;
    this->score_text_shape->y = 20;
    this->score_text_shape->h = score_text_surface->h;
    this->score_text_shape->w = score_text_surface->w;
    
    SDL_Surface* score_surface = TTF_RenderText_Solid(this->font, "0", *this->text_color);
    this->score_texture = SDL_CreateTextureFromSurface(render, score_surface);
    this->score_shape->x = score_text_shape->w + 20;
    this->score_shape->y = 20;
    this->score_shape->h = score_surface->h;
    this->score_shape->w = score_surface->w;
    
    SDL_FreeSurface(score_text_surface);
    SDL_FreeSurface(score_surface);
    
    switch (random_int(0, 3)) {
      case 0:
        this->player->direction_right();
        break;
      
      case 1:
        this->player->direction_up();
        break;
    
      case 2:
        this->player->direction_left();
        break;
      
      default:
        this->player->direction_down();
        break;    
    }
    this->nn->add_layer(this->input_layer);
    this->nn->add_layer(15);
    this->nn->add_layer(15);
    this->nn->add_layer(4);
    
    this->nn->get_layer(1)->set_activation_function(sigmoid);
    this->nn->get_layer(2)->set_activation_function(relu);
    this->nn->get_layer(3)->set_activation_function(sigmoid);
    this->input_layer->set_values(this->input_data);
    
    unsigned int genes_array_size = (this->nn->get_weight(0)->get_width() * this->nn->get_weight(0)->get_height()) + 
                                      (this->nn->get_weight(1)->get_width() * this->nn->get_weight(1)->get_height()) + 
                                      (this->nn->get_weight(2)->get_width() * this->nn->get_weight(2)->get_height());
    
    Gene* genes = new Gene[genes_array_size]; 
    unsigned int index = 0;
    for(Weights* weight : *(this->nn->get_weights())){
     
      Gene** gene_matrix = weight->get_weights()->get_matrix(); 
      
      for(unsigned int i = 0; i < weight->get_height(); i++){
        for(unsigned int j = 0; j < weight->get_width(); j++){
          genes[index] = gene_matrix[i][j];
          index++;
        }
      }
    }
    this->chromosome = new Chromosome(genes, genes_array_size, 100);
  }

  void AIScreen::execute(SDL_Renderer* render, bool& game_loop){
    this->nn->feedforward();
    Matrix<double>* result = nn->get_layer(3)->get_values();
    this->chromosome->show();
    double biggest = 0;
    unsigned int direction = 0;
    for(unsigned int i = 0; i < 4; i++){
      double actual_value = result->get_position_value(0, i);
      if(actual_value > biggest){
        biggest = actual_value;
        direction = i;
      }
    }
    
    switch (direction) {
      case 0:
        this->player->direction_up();
        break;
      
      case 1:
        this->player->direction_down();
        break;

      case 2:
        this->player->direction_left();
        break;

      default:
        this->player->direction_right();
        break;
    }


    int px = player->get_x();
    int py = player->get_y();
    int fx = food->get_x();
    int fy = food->get_y();

    int px_offset = PLAYER_W/2;
    int py_offset = PLAYER_H/2;
    int fx_offset = FOOD_W/2;
    int fy_offset = FOOD_H/2;

    this->input_data->update_value(0, 0, (double)WIDTH-px);
    this->input_data->update_value(0, 1, (double)px);
    this->input_data->update_value(0, 2, (double)py);
    this->input_data->update_value(0, 3, (double)HEIGHT-py);
    this->input_data->update_value(0, 4, sqrt(pow(px-fx, 2) + pow(py-fy, 2)));
    this->input_data->update_value(0, 5, (double)this->player->get_mov_x());
    this->input_data->update_value(0, 6, (double)this->player->get_mov_y());
    
    if(this->debug){
      SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
      SDL_RenderDrawLine(render, px, py+py_offset, WIDTH, py+py_offset);
      SDL_RenderDrawLine(render, 0, py+py_offset, px, py+py_offset);
      SDL_RenderDrawLine(render, px+px_offset, 0, px+px_offset, py);
      SDL_RenderDrawLine(render, px+px_offset, py, px+px_offset, HEIGHT);
      SDL_RenderDrawLine(render, px+py_offset, py+px_offset, fx+fx_offset, fy+fy_offset);
    }

    this->player->update_position();
    if(this->player->is_die()){
      cout << "GAME OVER!" << endl;
      game_loop = false;
      return;
    }else if(this->player->get_score() >= this->max_score){
      cout << "WON!" << endl;
      game_loop = false;
      return;
    }
    
    if(this->player->collision(this->food->get_x(), this->food->get_y())){
      this->food->update_position();
      this->player->update_score();

      unsigned int ai_score = this->player->get_score();
      SDL_Surface* score_surface = TTF_RenderText_Solid(this->font, to_string(ai_score).c_str(), *this->text_color);
      SDL_DestroyTexture(this->score_texture);
      this->score_texture = SDL_CreateTextureFromSurface(render, score_surface);
      this->score_shape->h = score_surface->h;
      this->score_shape->w = score_surface->w;
      SDL_FreeSurface(score_surface);
    
      cout << "AI score: " << ai_score << endl;
    }
    
    SDL_RenderCopy(render, this->score_text_texture, NULL, this->score_text_shape);
    SDL_RenderCopy(render, this->score_texture, NULL, this->score_shape);
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
    SDL_DestroyTexture(this->score_texture);
    SDL_DestroyTexture(this->score_text_texture);
    delete this->player;
    delete this->food;
    delete this->nn;
    delete this->chromosome;
    delete this->text_color;
    delete this->score_text_shape;
    delete this->score_shape;
  }
}
