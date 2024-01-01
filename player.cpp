#include "player.h"
#include "utils.h"
#include "constants.h"
#include <SDL2/SDL_timer.h>

namespace Players {
  unsigned int x, y;
  unsigned int score;
  unsigned int score_step;
  unsigned int max_score;
  unsigned int size;
  int mov_x, mov_y;
  int last_tick;

  Player::Player(){
    this->Player::randomize_position();
  }
  
  Player::Player(unsigned int score_step, unsigned int max_score){
    this->Player::randomize_position();
    this->score_step = score_step;
    this->max_score = max_score;
  }

  void Player::randomize_position(){
    this->x = Utils::get_random_pos(WIDTH, PLAYER_W);  
    this->y = Utils::get_random_pos(HEIGHT, PLAYER_H);
  }

  void Player::direction_up(){
    this->mov_y = -1;
    this->mov_x = 0;
  }

  void Player::direction_down(){
    this->mov_y = 1;
    this->mov_x = 0;
  }


  void Player::direction_left(){
    this->mov_x = -1;
    this->mov_y = 0;
  }

  
  void Player::direction_right(){
    this->mov_x = 1;
    this->mov_y = 0;
  }

  void Player::update_position(){
    if(Utils::passed_debounce_time(this->last_tick)){
      this->x += this->mov_x * PLAYER_W;
      this->y += this->mov_y * PLAYER_H;
      this->last_tick = SDL_GetTicks();
    }
  }

  bool Player::collision(unsigned int food_x, unsigned int food_y){
    return food_x == this->x && food_y == this->y;
  }
  
  void Player::update_score(){
    this->score += this->score_step;
    this->update_size();
  }

  unsigned int Player::get_x(){
    return this->x;
  }

  unsigned int Player::get_y(){
    return this->y;
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
}
