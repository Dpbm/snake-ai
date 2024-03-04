#include <SDL2/SDL_stdinc.h>
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
#include "../../helpers/utils.h"
#include "../../machine/machine.h"
#include "../../machine/layer.h"
#include "../../machine/activation.h"
#include "../../matrix/matrix.h"

using std::to_string;
using std::cout;
using std::endl;
using std::sqrt;
using std::acos;
using std::pow;
using Players::Player;
using Screens::Screen;
using Utils::random_int;
using Utils::get_random_x;
using Utils::get_random_y;
using Machine::NN;
using Layers::Layer;
using Activations::relu;
using Activations::sigmoid;
using Matrices::Matrix;

namespace GameAIScreen {

  AIScreen::AIScreen(SDL_Renderer* render){
    this->create_text(render);
    this->randomize_food_position();
    this->randomize_player_direction();

    this->nn->add_layer(this->input_layer);
    this->nn->add_layer(3);
    this->nn->add_layer(4);
    
    this->nn->get_layer(1)->set_activation_function(relu);
    this->nn->get_layer(2)->set_activation_function(sigmoid);
    this->input_layer->set_values(this->input_data);
    
    unsigned int genes_array_size = 0;
    for(size_t weight_i = 0; weight_i < this->nn->get_total_weights(); weight_i++){
      unsigned int w = this->nn->get_weight(weight_i)->get_width();
      unsigned int h = this->nn->get_weight(weight_i)->get_height();
      genes_array_size += w*h;
    } 

    for(size_t i = 0; i < this->total_individuals; i++)
      this->population[i].setup_choromosome(genes_array_size);
  }

  void AIScreen::update_input_data(){
    int px = this->player->get_x();  
    int py = this->player->get_y();  
    
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
    
    // this->input_data->update_value(0, 0, hip);
    this->input_data->update_value(0, 0, angle);

  }

  void AIScreen::load_genes_into_nn(){
    for(size_t weight_i = 0; weight_i < this->nn->get_total_weights(); weight_i++){
      unsigned int w = this->nn->get_weight(weight_i)->get_width();
      unsigned int h = this->nn->get_weight(weight_i)->get_height();

      this->nn->get_weight(weight_i)->load_weights(
        this->population[this->individual-1].get_genes_matrix(w, h)
      );
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

  void AIScreen::get_new_direction(){
    Matrix* result = this->nn->get_layer(2)->get_values();
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
  }

  void AIScreen::randomize_food_position(){
    this->fx = get_random_x(PLAYER_W); 
    this->fy = get_random_y(PLAYER_H); 
    this->food.set_position(this->fx, this->fy); 
  }

  void AIScreen::execute(SDL_Renderer* render, bool& game_loop){  
  
    this->load_genes_into_nn();
    this->update_input_data();
  
    this->nn->feedforward();
    this->get_new_direction();
    this->nn->get_layer(0)->get_values()->show();
    this->player->update_position();
    
    this->population[this->individual-1].get_chromosome()->show();
    bool ended_game = false;

    if(this->player->is_die()){
      cout << "GAME OVER!" << endl;
      ended_game = true;
    }
    
    
    if(this->player->collision(this->food.get_x(), this->food.get_y())){
      int ai_score = this->player->get_score();
      this->player->update_score();

      SDL_Surface* score_surface = TTF_RenderText_Solid(this->font, to_string(ai_score).c_str(), this->text_color);
      SDL_DestroyTexture(this->score_texture);
      this->score_texture = SDL_CreateTextureFromSurface(render, score_surface);
      this->score_shape.w = score_surface->w;
      SDL_FreeSurface(score_surface);
    
      cout << "AI score: " << ai_score << endl;
      if(ai_score > this->best_pontuation){
        this->best_pontuation = ai_score;
        this->best_individual = this->individual;
        this->update_best_individual_and_pontutaion_text(render);
      }
      this->reset(render); 
    }

    SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
    SDL_RenderDrawLine(render, this->player->get_x(), this->player->get_y(), this->fx, this->fy);
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
    
    if(ended_game){
      this->reset(render);
      return;
    }
  }

  void AIScreen::update_best_individual_and_pontutaion_text(SDL_Renderer* render){
    SDL_DestroyTexture(this->best_individual_texture);
    SDL_DestroyTexture(this->best_pontuation_texture);
    
    SDL_Surface* best_individual_surface = TTF_RenderText_Solid(this->font, to_string(this->individual).c_str(), this->text_color);
    this->best_individual_texture = SDL_CreateTextureFromSurface(render, best_individual_surface);
    this->best_individual_shape.w = best_individual_surface->w;
    
    SDL_Surface* best_pontuation_surface = TTF_RenderText_Solid(this->font, to_string(this->best_pontuation).c_str(), this->text_color);
    this->best_pontuation_texture = SDL_CreateTextureFromSurface(render, best_pontuation_surface);
    this->best_pontuation_shape.w = best_pontuation_surface->w;

    SDL_FreeSurface(best_individual_surface);
    SDL_FreeSurface(best_pontuation_surface);
  }

  Screen* AIScreen::key_event(const SDL_Keycode& key){
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

  void AIScreen::new_generation(){
    for(size_t i = 0; i < this->total_individuals; i++){
      if(i == this->best_individual-1)
        continue;
        
      this->population[i].get_chromosome()->copy_genes(
        this->population[this->best_individual-1].get_chromosome()->get_genes()
      );
      this->population[i].get_chromosome()->mutate(0.6);
    }

    
  }

  void AIScreen::reset(SDL_Renderer* render){
    this->points[this->individual-1] = this->player->get_score();

    this->individual++;
    if(this->individual > this->total_individuals){
      this->generation++;
      this->individual=1;
      this->new_generation();
      this->best_individual = 1;
      this->best_pontuation = 0;
      this->update_best_individual_and_pontutaion_text(render);
      this->randomize_food_position();
    }

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
    
    delete this->player;
    this->player = new Player(1, this->max_score);
    this->randomize_player_direction();
  }
  
  void AIScreen::create_text(SDL_Renderer* render){
    if(!this->font){
      cout << "Failed on getting font!" << TTF_GetError() << endl;
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

    if(score_texture == nullptr ||
       score_text_texture == nullptr ||
       generation_text_texture == nullptr || 
       generation_texture == nullptr || 
       individual_text_texture == nullptr ||
       individual_texture == nullptr ||
       best_individual_text_surface == nullptr ||
       best_individual_texture == nullptr ||
       best_pontuation_text_texture == nullptr ||
       best_pontuation_texture == nullptr){
      cout << "Failed on adding textures!" << TTF_GetError() << endl;
      exit(1);
      
    }
  }
}
