#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include "player.h"
#include "../helpers/utils.h"
#include "../helpers/constants.h"

using Players::LinkedList;
using Players::Node;
using Utils::get_random_pos;
using Utils::passed_debounce_time;

namespace Players {
  LinkedList* player;
  Node* head, tail;
  unsigned int score, score_step, max_score, size;
  int mov_x, mov_y, last_tick;
  bool died;

  Player::Player(unsigned int score_step, unsigned int max_score){
    this->randomize_position();
    this->score_step = score_step;
    this->max_score = max_score;
  }

  Player::~Player(){
    Node* actual_node = this->head;
    while(actual_node != nullptr){
      Node* tmp = actual_node;
      delete tmp->value;
      delete actual_node;
      actual_node = tmp->next;
    }
  }

  void Player::randomize_position(){
    unsigned int x = get_random_pos(WIDTH, PLAYER_W);  
    unsigned int y = get_random_pos(HEIGHT, PLAYER_H);
    this->add_body_part(x, y); 
  }
  
  void Player::add_body_part(unsigned int x, unsigned int y){
    Node* node = this->create_body_part(x, y);
    
    if(this->head == nullptr){
      this->head = node;
      this->tail = node;
      this->player = node;
      return;
    }
    
    this->tail->next = node;
    this->tail = node;
  }
  
  Node* Player::create_body_part(unsigned int x, unsigned int y){
    SDL_Rect* part = new SDL_Rect;
    part->x = x;
    part->y = y;
    part->h = PLAYER_H;
    part->w = PLAYER_W;
    
    Node* node = new Node;
    node->next = nullptr;
    node->value = part;
    
    return node;
  }

  void Player::direction_up(){
    if(this->mov_y != 0) 
      return;
  
    this->mov_y = -1;
    this->mov_x = 0;
  }

  void Player::direction_down(){
    if(this->mov_y != 0)
      return;

    this->mov_y = 1;
    this->mov_x = 0;
  }


  void Player::direction_left(){
    if(this->mov_x != 0)
      return;

    this->mov_x = -1;
    this->mov_y = 0;
  }

  
  void Player::direction_right(){
    if(this->mov_x != 0)
      return;
  
    this->mov_x = 1;
    this->mov_y = 0;
  }

  void Player::update_position(){
    if(passed_debounce_time(this->last_tick)){
      
      unsigned int old_pos_x = this->head->value->x; 
      unsigned int old_pos_y = this->head->value->y;
      
      unsigned int new_head_x = old_pos_x + (this->mov_x * PLAYER_W);
      unsigned int new_head_y = old_pos_y + (this->mov_y * PLAYER_H);

      this->head->value->x = new_head_x;
      this->head->value->y = new_head_y;

      this->died = this->border_head_collision() || this->head_tail_collision();  

      Node* actual_part = this->head->next;
      while(actual_part != nullptr){ 
        unsigned int tmp_x = actual_part->value->x;
        unsigned int tmp_y = actual_part->value->y;

        actual_part->value->x = old_pos_x;
        actual_part->value->y = old_pos_y;
      
        old_pos_x = tmp_x;
        old_pos_y = tmp_y;
        actual_part = actual_part->next;
      }

      this->last_tick = SDL_GetTicks();
    }
  }

  bool Player::collision(unsigned int food_x, unsigned int food_y){
    return food_x == this->head->value->x && food_y == this->head->value->y;
  }
  
  void Player::update_score(){
    this->score += this->score_step;
    this->Player::update_size();
    this->Player::add_body_part(this->tail->value->x, this->tail->value->y);
  }

  unsigned int Player::get_x(){
    return this->head->value->x;
  }

  unsigned int Player::get_y(){
    return this->head->value->y;
  }

  unsigned int Player::get_score(){
    return this->score;
  }

  void Player::update_size(){
    this->size ++;
  }

  unsigned int Player::get_size(){
    return this->size;
  }

  int Player::get_mov_x(){
    return this->mov_x;
  }

  int Player::get_mov_y(){
    return this->mov_y;
  }

  bool Player::border_head_collision(){
    unsigned int head_x = this->head->value->x; 
    unsigned int head_y = this->head->value->y;
    return head_x < 0 || head_x > WIDTH || head_y < 0 || head_y > HEIGHT;
  }

  bool Player::head_tail_collision(){
    Node* actual_bpart = this->head->next;
    while(actual_bpart != nullptr){

      if(actual_bpart->value->x == this->head->value->x && 
        actual_bpart->value->y == this->head->value->y)
          return true;

      actual_bpart = actual_bpart->next;
    }
    return false;
  }

  bool Player::is_die(){
    return this->died;
  }
  
  void Player::render(SDL_Renderer* render){
    Node* actual_bpart = this->head;
    while(actual_bpart != nullptr){
      SDL_SetRenderDrawColor(render, 0, 0, 255, 255);
      SDL_RenderFillRect(render, actual_bpart->value);
      SDL_SetRenderDrawColor(render, 0, 0, 0, 255);

      actual_bpart = actual_bpart->next;
    }
  }
}
