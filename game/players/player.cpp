#include <SDL2/SDL_timer.h>
#include <cstdint>
#include "player.h"
#include "../../helpers/utils.h"
#include "../../helpers/constants.h"

using Utils::random_int;

namespace Players {
  Player::Player(){}

  Player::Player(uint8_t score_step, uint8_t board_w, uint8_t board_h){
    this->set_score_step(score_step);
    this->random_pos(board_w, board_h);
    this->random_dir();
  }
  
  Player::Player(uint8_t score_step, int16_t x, int16_t y, Directions dir){
    this->set_score_step(score_step);
    this->set_pos(x, y);
    this->set_dir(dir);
  }  

  void Player::random_pos(uint8_t w, uint8_t h){
    int16_t x = random_int(0,h);
    int16_t y = random_int(0,w);
    this->add_body_part(x, y); 
  }

  void Player::set_score_step(uint8_t score_step){
    this->score_step = score_step;
  }

  void Player::add_body_part(int16_t x, int16_t y){
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


  int16_t Player::get_x(){
    return this->head->value.x;
  }
  
  int16_t Player::get_y(){
    return this->head->value.y;
  }
   
  Node* Player::create_body_part(int16_t x, int16_t y){
    Node* node = new Node;
    node->next = nullptr;
    node->value = vec2{x,y};
    return node;
  }

  void Player::set_dir(Directions dir){
    switch (dir) {
      case UP:
        this->direction_up();
        break;
      case DOWN: 
        this->direction_down();
        break;
      case LEFT:
        this->direction_left();
        break;
      case RIGHT:
        this->direction_right();
        break;
      default:
        break;
    }
  }

  bool Player::passed_debounce_time(){
    return  SDL_GetTicks() - this->last_tick >= DEBOUNCE_TIME;
  }

  void Player::set_pos(int16_t x, int16_t y){
    if(this->head == nullptr)
      this->add_body_part(x, y);
    else{
      this->head->value.x = x;
      this->head->value.y = y;
      this->old_tail_pos = this->head->value;
    }  
  }

  void Player::set_last_tick(){
    this->last_tick = DEBOUNCE_TIME;
  }

  void Player::random_dir(){
    this->set_dir((Directions)random_int(0, 3)); 
  }
  
  void Player::direction_up(){
    if(this->mov_x != 0) 
      return;
    this->dir = UP; 
    this->mov_y = 0;
    this->mov_x = -1;
  }

  void Player::direction_down(){
    if(this->mov_x != 0)
      return;

    this->dir = DOWN;
    this->mov_y = 0;
    this->mov_x = 1;
  }


  void Player::direction_left(){
    if(this->mov_y != 0)
      return;

    this->dir = LEFT;
    this->mov_x = 0;
    this->mov_y = -1;
  }

  
  void Player::direction_right(){
    if(this->mov_y != 0)
      return;
  
    this->dir = RIGHT;
    this->mov_x = 0;
    this->mov_y = 1;
  }

  void Player::update_pos(){
    if(this->passed_debounce_time() and !this->died){
      this->mov_body();
      this->last_tick = SDL_GetTicks();
    }
  }

  void Player::mov_body(){
    int16_t old_pos_x = this->head->value.x; 
    int16_t old_pos_y = this->head->value.y;
     
    vec2 old_tail = this->tail->value; 
  
    int16_t new_head_x = old_pos_x + (int)this->mov_x;
    int16_t new_head_y = old_pos_y + (int)this->mov_y;
    

    this->head->value.x = new_head_x;
    this->head->value.y = new_head_y;

    Node* actual_part = this->head->next;
    while(actual_part != nullptr){ 
      int16_t tmp_x = actual_part->value.x;
      int16_t tmp_y = actual_part->value.y;

      actual_part->value.x = old_pos_x;
      actual_part->value.y = old_pos_y;
    
      old_pos_x = tmp_x;
      old_pos_y = tmp_y;
      actual_part = actual_part->next;
    }

    this->old_tail_pos = old_tail;
  }

  void Player::set_died(){
    this->died = true;
  }

  LinkedList* Player::get_player(){
    return this->player;
  }
  
  Node* Player::get_head(){
    return this->head;
  }
  
  Node* Player::get_tail(){
    return this->tail;
  }

  void Player::update_score(){
    this->score += this->score_step;
    this->add_body_part(this->old_tail_pos.x, this->old_tail_pos.y);
  }

  vec2 Player::get_old_tail_pos(){
    return this->old_tail_pos;
  }

  uint16_t Player::get_score(){
    return this->score;
  }
  Directions Player::get_dir(){
    return this->dir;
  }

  uint8_t Player::get_score_step(){
    return this->score_step;
  }

  int8_t Player::get_mov_x(){
    return this->mov_x;
  }

  int8_t Player::get_mov_y(){
    return this->mov_y;
  }

  void Player::head_tail_collision(){
    Node* actual_bpart = this->head->next;
    while(actual_bpart != nullptr){

      if(actual_bpart->value.x == this->head->value.x && 
        actual_bpart->value.y == this->head->value.y){
          this->died = true;
          break;
        }
      actual_bpart = actual_bpart->next;
    }
  }

  bool Player::is_dead(){
    return this->died;
  }

  void Player::clear_pointers(){
    Node* actual_node = this->head;
    while(actual_node != nullptr){
      Node* next = actual_node->next;
      delete actual_node;
      actual_node = next;
    }
  }

  Player::~Player(){
    this->clear_pointers();
  }
}
