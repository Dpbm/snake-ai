#pragma once

#include "player.h"
#include "../../qubo/qubo.h"
#include "../../helpers/utils.h"
#include <cstdint>

using Qubo::QuboFunc;
using Utils::vec2;

namespace Players{
  class QuboPlayer : public Player {
    public:   
      QuboPlayer(uint8_t board_w, uint8_t board_h);
      ~QuboPlayer();

      void next_mov(const vec2& food);

    private:
      QuboFunc* qubo = nullptr;
      uint8_t board_w = 0;
      uint8_t board_h = 0;

      bool will_collide_itself(int16_t x, int16_t y);
  
  
      bool will_collide_top_border();
      bool will_collide_bottom_border();
      bool will_collide_left_border();
      bool will_collide_right_border();
  
      void get_distances_right(int16_t fx, int16_t fy, double* q0, double* q1, double* q2);
      void get_distances_left(int16_t fx, int16_t fy, double* q0, double* q1, double* q2);
      void get_distances_up(int16_t fx, int16_t fy, double* q0, double* q1, double* q2);
      void get_distances_down(int16_t fx, int16_t fy, double* q0, double* q1, double* q2);
  
      void move_down_right();
      void move_up_left();
  };

};
