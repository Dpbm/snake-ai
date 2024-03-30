#include <SDL2/SDL_timer.h>
#include <cstdint>
#include "player.h"
#include "../../helpers/utils.h"

using Utils::random_int;
using Utils::passed_debounce_time;

namespace Players {
  Player::Player(){}

  Player::Player(uint8_t score_step, uint16_t max_score, uint8_t board_w, uint8_t board_h){
    this->score_step = score_step;
    this->max_score = max_score;
    this->random_pos(board_w, board_h);
    this->random_dir();
  }

  void Player::random_pos(uint8_t w, uint8_t h){
    int16_t x = random_int(0,h);
    int16_t y = random_int(0,w);
    this->add_body_part(x, y); 
  }
  
  void Player::add_body_part(int16_t x, int16_t y){
    if(head != nullptr){
    std::cout << " x " << this->head->value.x << " y " << this->head->value.y << std::endl;
    std::cout << " ax " << this->tail->value.x << " y " << this->tail->value.y << std::endl;
      }

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

  void Player::random_dir(){
    this->dir = (Directions)random_int(0, 3);
    
    switch ((int)this->dir) {
      case UP:
        this->direction_up();
        break;
      case DOWN:
        this->direction_down();
        break;
      case LEFT:
        this->direction_left();
        break;
      default:
        this->direction_right();
    }
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
    if(passed_debounce_time(this->last_tick) and !this->died){
      int16_t old_pos_x = this->head->value.x; 
      int16_t old_pos_y = this->head->value.y;
    
      int16_t new_head_x = old_pos_x + this->mov_x;
      int16_t new_head_y = old_pos_y + this->mov_y;

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
      this->last_tick = SDL_GetTicks();
    }
  }

  void Player::set_died(){
    this->died = true;
  }

  LinkedList* Player::get_player(){
    return this->player;
  }

  void Player::update_score(){
    this->score += this->score_step;
    this->size ++;
    this->add_body_part(this->tail->value.x, this->tail->value.y);
  }

  unsigned int Player::get_score(){
    return this->score;
  }

  unsigned int Player::get_size(){
    return this->size;
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
  

  void Player::set_score_step(uint8_t score_step){
    this->score_step = score_step;
  }

  void Player::set_max_score(uint16_t max_score){
    this->max_score = max_score;
  }

  Player::~Player(){
    Node* actual_node = this->head;
    while(actual_node != nullptr){
      Node* next = actual_node->next;
      delete actual_node;
      actual_node = next;
    }
  }
}
