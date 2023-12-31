#include "player.h"
#include "utils.h"
#include "constants.h"

namespace Players {
  unsigned int x, y;
  unsigned int score;
  unsigned int score_step;
  unsigned int max_score;

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

  void Player::move_up(){
    if(this->y > 0)
      this->y -= PLAYER_H;
  }

  void Player::move_down(){
    if(this->y < HEIGHT - PLAYER_H)
      this->y += PLAYER_H;
  }


  void Player::move_left(){
    if(this->x > 0)
      this->x -= PLAYER_W;
  }

  
  void Player::move_right(){
    if(this->x < WIDTH - PLAYER_W)
      this->x += PLAYER_W;
  }
  
  bool Player::collision(unsigned int food_x, unsigned int food_y){
    return food_x == this->x && food_y == this->y;
  }
  
  void Player::update_score(){
    this->score += this->score_step;
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
}
