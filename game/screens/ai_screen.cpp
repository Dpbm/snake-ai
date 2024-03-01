#include <cmath>
#include <cstddef>
#include <iostream>
#include <string>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_surface.h>
#include "ai_screen.h"
#include "../player.h"
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

  AIScreen::AIScreen(SDL_Renderer* render){
    if(!this->font){
      cout << "Failed on getting font!" << endl;
      cout << TTF_GetError() << endl;
      exit(1);
    }
    SDL_Surface* score_text_surface = TTF_RenderText_Solid(this->font, "Score ", this->text_color);
    this->score_text_texture = SDL_CreateTextureFromSurface(render, score_text_surface);
    this->score_text_shape = SDL_Rect{20, 20, score_text_surface->w, score_text_surface->h};
   
    SDL_Surface* score_surface = TTF_RenderText_Solid(this->font, "0", this->text_color);
    this->score_texture = SDL_CreateTextureFromSurface(render, score_surface);
    this->score_shape = SDL_Rect{score_text_shape.w+20, 20, score_surface->w, score_surface->h};
    
    SDL_Surface* individual_text_surface = TTF_RenderText_Solid(this->font, "Indiv. ", this->text_color);
    this->individual_text_texture = SDL_CreateTextureFromSurface(render, individual_text_surface);
    this->individual_text_shape = SDL_Rect{20, 50, individual_text_surface->w, individual_text_surface->h};
    
    SDL_Surface* individual_surface = TTF_RenderText_Solid(this->font, "1", this->text_color);
    this->individual_texture = SDL_CreateTextureFromSurface(render, individual_surface);
    this->individual_shape = SDL_Rect{individual_text_shape.w+20, 50, individual_surface->w, individual_surface->h};
    
    SDL_Surface* generation_text_surface = TTF_RenderText_Solid(this->font, "Gen. ", this->text_color);
    this->generation_text_texture = SDL_CreateTextureFromSurface(render, generation_text_surface);
    this->generation_text_shape = SDL_Rect{20, 80, generation_text_surface->w, generation_text_surface->h};
    
    SDL_Surface* generation_surface = TTF_RenderText_Solid(this->font, "1", this->text_color);
    this->generation_texture = SDL_CreateTextureFromSurface(render, generation_surface);
    this->generation_shape = SDL_Rect{generation_text_shape.w+20, 80, generation_surface->w, generation_surface->h};
    
    SDL_Surface* best_individual_text_surface = TTF_RenderText_Solid(this->font, "Best ", this->text_color);
    this->best_individual_text_texture = SDL_CreateTextureFromSurface(render, best_individual_text_surface);
    this->best_individual_text_shape = SDL_Rect{20, 110, best_individual_text_surface->w, best_individual_text_surface->h};
    
    SDL_Surface* best_individual_surface = TTF_RenderText_Solid(this->font, "1", this->text_color);
    this->best_individual_texture = SDL_CreateTextureFromSurface(render, best_individual_surface);
    this->best_individual_shape = SDL_Rect{best_individual_text_shape.w+20, 110, best_individual_surface->w, best_individual_surface->h};
    
    SDL_Surface* best_pontuation_text_surface = TTF_RenderText_Solid(this->font, "Best pon. ", this->text_color);
    this->best_pontuation_text_texture = SDL_CreateTextureFromSurface(render, best_pontuation_text_surface);
    this->best_pontuation_text_shape = SDL_Rect{20, 140, best_pontuation_text_surface->w, best_pontuation_text_surface->h};
    
    SDL_Surface* best_pontuation_surface = TTF_RenderText_Solid(this->font, "0", this->text_color);
    this->best_pontuation_texture = SDL_CreateTextureFromSurface(render, best_pontuation_surface);
    this->best_pontuation_shape = SDL_Rect{best_pontuation_text_shape.w+20, 140, best_pontuation_surface->w, best_pontuation_surface->h};
    
    SDL_FreeSurface(score_text_surface);
    SDL_FreeSurface(score_surface);
    SDL_FreeSurface(generation_text_surface);
    SDL_FreeSurface(generation_surface);
    SDL_FreeSurface(individual_text_surface);
    SDL_FreeSurface(individual_surface);
    SDL_FreeSurface(best_individual_text_surface);
    SDL_FreeSurface(best_individual_surface);
    SDL_FreeSurface(best_pontuation_text_surface);
    SDL_FreeSurface(best_pontuation_surface);

    this->randomize_player_direction();
    
    this->nn->add_layer(this->input_layer);
    this->nn->add_layer(15);
    this->nn->add_layer(15);
    this->nn->add_layer(4);
    
    this->nn->get_layer(1)->set_activation_function(sigmoid);
    this->nn->get_layer(2)->set_activation_function(relu);
    this->nn->get_layer(3)->set_activation_function(sigmoid);
    this->input_layer->set_values(this->input_data);
    
    unsigned int genes_array_size = 0;
    for(size_t weight_i = 0; weight_i < this->nn->get_total_weights(); weight_i++){
      unsigned int w = this->nn->get_weight(weight_i)->get_width();
      unsigned int h = this->nn->get_weight(weight_i)->get_height();
      genes_array_size += w*h;
    } 
    
    for(size_t individual = 0; individual < this->total_individuals; individual++)
      this->population[individual].add_genes(genes_array_size);

    this->load_genes_into_nn();
  }

  void AIScreen::load_genes_into_nn(){
    Gene* individual_genes = this->population[this->individual-1].get_genes();
    for(size_t weight_i = 0; weight_i < this->nn->get_total_weights(); weight_i++){
      unsigned int w = this->nn->get_weight(weight_i)->get_width();
      unsigned int h = this->nn->get_weight(weight_i)->get_height();

      Matrix* new_weights = new Matrix(w, h);
      int gene_index = 0;
      for(size_t i = 0; i < h; i++){
        for(size_t j = 0; j < w; j++){
          new_weights->update_value(i, j, individual_genes[gene_index].get_gene_value());        
          gene_index++;
        }
      }

      this->nn->get_weight(weight_i)->load_weights(new_weights);
    }
  }

  void AIScreen::randomize_player_direction(){
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
  }

  void AIScreen::execute(SDL_Renderer* render, bool& game_loop){
    
    this->nn->feedforward();
    Matrix* result = this->nn->get_layer(3)->get_values();
    double biggest = 0;
    unsigned int direction = 0;
    for(size_t i = 0; i < 4; i++){
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
    int fx = food.get_x();
    int fy = food.get_y();

    int px_offset = PLAYER_W/2;
    int py_offset = PLAYER_H/2;
    int fx_offset = FOOD_W/2;
    int fy_offset = FOOD_H/2;

    //this->input_data->update_value(0, 0, (double)PLAY_WIDTH-px);
    this->input_data->update_value(0, 0, (double)px);
    this->input_data->update_value(0, 1, (double)py);
    //this->input_data->update_value(0, 3, (double)HEIGHT-py);
    this->input_data->update_value(0, 2, sqrt(pow(px-fx, 2) + pow(py-fy, 2)));
    this->input_data->update_value(0, 3, (double)(abs(this->player->get_mov_x())));
    this->input_data->update_value(0, 4, (double)(abs(this->player->get_mov_y()+1)));
    
    if(this->debug){
      SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
      SDL_RenderDrawLine(render, px, py+py_offset, PLAY_WIDTH, py+py_offset);
      SDL_RenderDrawLine(render, 0, py+py_offset, px, py+py_offset);
      SDL_RenderDrawLine(render, px+px_offset, 0, px+px_offset, py);
      SDL_RenderDrawLine(render, px+px_offset, py, px+px_offset, HEIGHT);
      SDL_RenderDrawLine(render, px+py_offset, py+px_offset, fx+fx_offset, fy+fy_offset);
    }

    this->player->update_position();
    bool ended_game = false;

    if(this->player->is_die()){
      cout << "GAME OVER!" << endl;
      ended_game = true;
    }else if(this->player->get_score() >= this->max_score){
      cout << "WON!" << endl;
      ended_game = true;
    }
    
    if(ended_game){
      this->reset(render);
      return;
    }
    
    if(this->player->collision(this->food.get_x(), this->food.get_y())){
      this->food.update_position();
      this->player->update_score();

      unsigned int ai_score = this->player->get_score();
      SDL_Surface* score_surface = TTF_RenderText_Solid(this->font, to_string(ai_score).c_str(), this->text_color);
      SDL_DestroyTexture(this->score_texture);
      this->score_texture = SDL_CreateTextureFromSurface(render, score_surface);
      this->score_shape.w = score_surface->w;
      SDL_FreeSurface(score_surface);
    
      cout << "AI score: " << ai_score << endl;
    }
    
    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    SDL_RenderFillRect(render, &this->screen_separator);
    SDL_RenderCopy(render, this->score_text_texture, NULL, &this->score_text_shape);
    SDL_RenderCopy(render, this->score_texture, NULL, &this->score_shape);
    SDL_RenderCopy(render, this->generation_text_texture, NULL, &this->generation_text_shape);
    SDL_RenderCopy(render, this->generation_texture, NULL, &this->generation_shape);
    SDL_RenderCopy(render, this->individual_text_texture, NULL, &this->individual_text_shape);
    SDL_RenderCopy(render, this->individual_texture, NULL, &this->individual_shape);
    SDL_RenderCopy(render, this->best_individual_text_texture, NULL, &this->best_individual_text_shape);
    SDL_RenderCopy(render, this->best_individual_texture, NULL, &this->best_individual_shape);
    SDL_RenderCopy(render, this->best_pontuation_text_texture, NULL, &this->best_pontuation_text_shape);
    SDL_RenderCopy(render, this->best_pontuation_texture, NULL, &this->best_pontuation_shape);
    this->food.render(render);
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
    SDL_DestroyTexture(this->generation_texture);
    SDL_DestroyTexture(this->generation_text_texture);
    SDL_DestroyTexture(this->individual_texture);
    SDL_DestroyTexture(this->individual_text_texture);
    SDL_DestroyTexture(this->best_individual_texture);
    SDL_DestroyTexture(this->best_individual_text_texture);
    SDL_DestroyTexture(this->best_pontuation_texture);
    SDL_DestroyTexture(this->best_pontuation_text_texture);
    delete this->player;
    delete this->nn;
    delete[] this->population;
  }
  
  void AIScreen::reset(SDL_Renderer* render){
    delete this->player;
  
    this->player = new Player(1, this->max_score);
    this->food.update_position();

    int player_score = player->get_score();

    this->points[this->individual-1] = player_score;
    cout << "points: ";
    for(size_t i = 0; i < this->individual; i++)
      cout << points[i] << " ";
    cout << endl;

    if(player_score > this->best_pontuation){
      this->best_pontuation = player_score;
      this->best_individual = this->individual;
      
      SDL_DestroyTexture(this->best_individual_texture);
      SDL_DestroyTexture(this->best_pontuation_texture);
      
      SDL_Surface* best_individual_surface = TTF_RenderText_Solid(this->font, to_string(this->individual).c_str(), this->text_color);
      this->best_individual_texture = SDL_CreateTextureFromSurface(render, best_individual_surface);
      this->best_individual_shape.w = best_individual_surface->w;
      
      SDL_Surface* best_pontuation_surface = TTF_RenderText_Solid(this->font, to_string(player_score).c_str(), this->text_color);
      this->best_pontuation_texture = SDL_CreateTextureFromSurface(render, best_pontuation_surface);
      this->best_pontuation_shape.w = best_pontuation_surface->w;

      SDL_FreeSurface(best_individual_surface);
      SDL_FreeSurface(best_pontuation_surface);
    }

    this->individual++;
    if(this->individual > this->total_individuals){ 
      this->generation++;
      this->individual=1;
    }
    this->load_genes_into_nn();
    this->randomize_player_direction();

    
    SDL_DestroyTexture(this->score_texture);
    SDL_Surface* score_surface = TTF_RenderText_Solid(this->font, "0", this->text_color);
    this->score_texture = SDL_CreateTextureFromSurface(render, score_surface);
    this->score_shape.w = score_surface->w;
    SDL_FreeSurface(score_surface);
    
    SDL_DestroyTexture(this->generation_texture);
    SDL_Surface* generation_surface = TTF_RenderText_Solid(this->font, to_string(this->generation).c_str(), this->text_color);
    this->generation_texture = SDL_CreateTextureFromSurface(render, generation_surface);
    this->generation_shape.w = generation_surface->w;
    SDL_FreeSurface(generation_surface);
    
    SDL_DestroyTexture(this->individual_texture);
    SDL_Surface* individual_surface = TTF_RenderText_Solid(this->font, to_string(this->individual).c_str(), this->text_color);
    this->individual_texture = SDL_CreateTextureFromSurface(render, individual_surface);
    this->individual_shape.w = individual_surface->w;
    SDL_FreeSurface(individual_surface);
  }
}
