#include "player.h"
#include "body_part.h"
#include "utils.h"
#include "constants.h"
#include <SDL2/SDL_timer.h>

namespace Players {
  Players::LinkedList* player;
  Players::Node* head;
  Players::Node* tail;
  unsigned int score;
  unsigned int score_step;
  unsigned int max_score;
  unsigned int size;
  int mov_x, mov_y;
  int last_tick;
  bool game_over;

  Player::Player(){
    this->Player::randomize_position();
  }
  
  Player::Player(unsigned int score_step, unsigned int max_score){
    this->Player::randomize_position();
    this->score_step = score_step;
    this->max_score = max_score;
  }

  void Player::randomize_position(){
    unsigned int x = Utils::get_random_pos(WIDTH, PLAYER_W);  
    unsigned int y = Utils::get_random_pos(HEIGHT, PLAYER_H);
    this->Player::add_body_part(x, y); 
  }

  void Player::direction_up(){
    if(this->mov_y == 0){
      this->mov_y = -1;
      this->mov_x = 0;
    }
  }

  void Player::direction_down(){
    if(this->mov_y == 0){
      this->mov_y = 1;
      this->mov_x = 0;
    }
  }


  void Player::direction_left(){
    if(this->mov_x == 0){
      this->mov_x = -1;
      this->mov_y = 0;
    }
  }

  
  void Player::direction_right(){
    if(this->mov_x == 0){
      this->mov_x = 1;
      this->mov_y = 0;
    }
  }

  void Player::update_position(){
    if(Utils::passed_debounce_time(this->last_tick)){
      
      unsigned int old_pos_x = this->head->value->get_x(); 
      unsigned int old_pos_y = this->head->value->get_y();
      
      unsigned int new_head_x = old_pos_x + (this->mov_x * PLAYER_W);
      unsigned int new_head_y = old_pos_y + (this->mov_y * PLAYER_H);
      this->head->value->update_position(new_head_x, new_head_y);
      this->Player::check_game_over();  

      Players::Node* actual_part = this->head->next;

      while(actual_part != nullptr){ 
        unsigned int tmp_x = actual_part->value->get_x();
        unsigned int tmp_y = actual_part->value->get_y();

        actual_part->value->update_position(old_pos_x, old_pos_y);
      
        old_pos_x = tmp_x;
        old_pos_y = tmp_y;
        actual_part = actual_part->next;
      }

      this->last_tick = SDL_GetTicks();
    }
  }

  bool Player::collision(unsigned int food_x, unsigned int food_y){
    return food_x == this->head->value->get_x() && food_y == this->head->value->get_y();
  }
  
  void Player::update_score(){
    this->score += this->score_step;
    this->Player::update_size();
    this->Player::add_body_part(this->tail->value->get_x(), this->tail->value->get_y());
  }

  unsigned int Player::get_x(){
    return this->head->value->get_x();
  }

  unsigned int Player::get_y(){
    return this->head->value->get_y();
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

  void Player::add_body_part(unsigned int x, unsigned int y){
    Players::Node* node = this->Player::create_body_part(x, y);
    
    if(this->head == nullptr){
      this->head = node;
      this->tail = node;
      this->player = node;
      return;
    }
    
    this->tail->next = node;
    this->tail = node;
  }

  Players::Node* Player::create_body_part(unsigned int x, unsigned int y){
    BodyParts::BodyPart* part = new BodyParts::BodyPart(x,y);
    
    Players::Node* node = new Players::Node;
    node->next = nullptr;
    node->value = part;
    
    return node;
  }

  Players::LinkedList* Player::get_body(){
    return this->player;
  }

  void Player::check_game_over(){
    this->game_over = this->Player::border_head_collision() || this->Player::head_tail_collision();
  }

  bool Player::border_head_collision(){
    unsigned int head_x = this->head->value->get_x(); 
    unsigned int head_y = this->head->value->get_y();
    return head_x < 0 || head_x > WIDTH || head_y < 0 || head_y > HEIGHT;
  }

  bool Player::head_tail_collision(){
    Players::Node* actual_bpart = this->head->next;
    while(actual_bpart != nullptr){
      if(
        actual_bpart->value->get_x() == this->head->value->get_x() && 
        actual_bpart->value->get_y() == this->head->value->get_y())
          return true;

      actual_bpart = actual_bpart->next;
    }
    return false;
  }

  bool Player::is_game_over(){
    return this->game_over;
  }
}
