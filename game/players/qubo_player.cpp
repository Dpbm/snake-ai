#include <cstdint>
#include "qubo_player.h"
#include "../../qubo/qubo.h"
#include "../../helpers/utils.h"

using Qubo::QuboFunc;
using Utils::vec2;
using Utils::distance;

namespace Players {
  QuboPlayer::QuboPlayer(uint8_t board_w, uint8_t board_h) : Player(board_w, board_h){
    this->board_w = board_w;
    this->board_h = board_h;
    this->qubo = new QuboFunc((board_h*board_h) + 10);
  }
  
  bool QuboPlayer::will_collide_itself(int16_t x, int16_t y){
    bool will_collide = false;
    Node* actual_bpart = this->head->next;
    while(actual_bpart != nullptr){

      if(actual_bpart->value.x == x && 
        actual_bpart->value.y == y){
          will_collide = true;
          break;
        }
      actual_bpart = actual_bpart->next;
    }
    return will_collide;
  }

  bool QuboPlayer::will_collide_top_border(){
    return this->get_x() <= 0;
  }
  
  bool QuboPlayer::will_collide_bottom_border(){
    return this->get_x() >= this->board_h-1;
  }
  
  bool QuboPlayer::will_collide_left_border(){
    return this->get_y() <= 0;
  }
  
  bool QuboPlayer::will_collide_right_border(){
    return this->get_x() >= this->board_w-1;
  }

  void QuboPlayer::next_mov(const vec2& food){
    double q0 = 10000.0; //distance forward
    double q1 = 10000.0; //distance down/right
    double q2 = 10000.0; //distance up/left
    
    switch (this->dir) {
      case RIGHT:
        this->get_distances_right(food.x, food.y, &q0, &q1, &q2);
        break;
      case LEFT:
        this->get_distances_left(food.x, food.y, &q0, &q1, &q2);
        break;
      case UP:
        this->get_distances_up(food.x, food.y, &q0, &q1, &q2);
        break;
      case DOWN:
        this->get_distances_up(food.x, food.y, &q0, &q1, &q2);
        break;
      default:
        break;
    }

    uint8_t* next_mov = this->qubo->minimize(q0, q1, q2);
    
    if(next_mov[0] == 0 && next_mov[1] == 0 && next_mov[2] == 1)
      this->move_down_right();
    else if(next_mov[0] == 0 && next_mov[1] == 1 && next_mov[2] == 0)
      this->move_up_left();

    delete next_mov;
  } 

  void QuboPlayer::get_distances_right(int16_t fx, int16_t fy, double* q0, double* q1, double* q2){
    if(!this->will_collide_itself(this->get_x(), this->get_y()+1) && !this->will_collide_right_border())
      *q0 = distance(this->get_x(), this->get_y()+1, fx, fy);  
  
    if(!this->will_collide_itself(this->get_x()+1, this->get_y()) && !this->will_collide_bottom_border())
      *q1 = distance(this->get_x()+1, this->get_y(), fx, fy);

    if(!this->will_collide_itself(this->get_x()-1, this->get_y()) && !this->will_collide_top_border())
      *q2 = distance(this->get_x()-1, this->get_y(), fx, fy);
  }


  void QuboPlayer::get_distances_left(int16_t fx, int16_t fy, double* q0, double* q1, double* q2){
    if(!this->will_collide_itself(this->get_x(), this->get_y()-1) && !this->will_collide_left_border())
      *q0 = distance(this->get_x(), this->get_y()-1, fx, fy);  
  
    if(!this->will_collide_itself(this->get_x()+1, this->get_y()) && !this->will_collide_bottom_border())
      *q1 = distance(this->get_x()+1, this->get_y(), fx, fy);

    if(!this->will_collide_itself(this->get_x()-1, this->get_y()) && !this->will_collide_top_border())
      *q2 = distance(this->get_x()-1, this->get_y(), fx, fy);
  }
  
  void QuboPlayer::get_distances_up(int16_t fx, int16_t fy, double* q0, double* q1, double* q2){
    if(!this->will_collide_itself(this->get_x()-1, this->get_y()) && !this->will_collide_top_border())
      *q0 = distance(this->get_x()-1, this->get_y(), fx, fy);  
  
    if(!this->will_collide_itself(this->get_x(), this->get_y()+1) && !this->will_collide_right_border())
      *q1 = distance(this->get_x(), this->get_y()+1, fx, fy);

    if(!this->will_collide_itself(this->get_x(), this->get_y()-1) && !this->will_collide_left_border())
      *q2 = distance(this->get_x(), this->get_y()-1, fx, fy);
  }
  
  void QuboPlayer::get_distances_down(int16_t fx, int16_t fy, double* q0, double* q1, double* q2){
    if(!this->will_collide_itself(this->get_x()+1, this->get_y()) && !this->will_collide_bottom_border())
      *q0 = distance(this->get_x()+1, this->get_y(), fx, fy);  
  
    if(!this->will_collide_itself(this->get_x(), this->get_y()+1) && !this->will_collide_right_border())
      *q1 = distance(this->get_x(), this->get_y()+1, fx, fy);

    if(!this->will_collide_itself(this->get_x(), this->get_y()-1) && !this->will_collide_left_border())
      *q2 = distance(this->get_x(), this->get_y()-1, fx, fy);
  }


  void QuboPlayer::move_down_right(){
    switch (this->dir) {
      case RIGHT:
        this->direction_down();
        break;
      case LEFT:
        this->direction_down();
        break;
      case UP:
        this->direction_right();
        break;
      case DOWN:
        this->direction_right();
        break;
      default:
        break;
    }
  }
  
  void QuboPlayer::move_up_left(){
    switch (this->dir) {
      case RIGHT:
        this->direction_up();
        break;
      case LEFT:
        this->direction_up();
        break;
      case UP:
        this->direction_left();
        break;
      case DOWN:
        this->direction_left();
        break;
      default:
        break;
    }
  }

  QuboPlayer::~QuboPlayer(){
    delete this->qubo;
  } 

}
