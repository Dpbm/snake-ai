#pragma once

#include <cstdint>
#include "../../helpers/utils.h"

using Utils::vec2;

namespace Players {
  enum Directions{UP=0, DOWN=1, LEFT=2, RIGHT=3};
  
  struct Node{
    vec2 value;
    Node* next;
  };

  typedef struct Node Node;
  typedef struct Node LinkedList;
  
  class Player{
    public:
      Player();
      Player(uint8_t score_step, uint8_t board_w, uint8_t board_h);
      void random_pos(uint8_t w, uint8_t h);
      void random_dir();
      
      void update_pos();
      void direction_up();
      void direction_down();
      void direction_left();
      void direction_right();
      void update_score();
      uint16_t get_score();
      void reset_score();
      int8_t get_mov_x();
      int8_t get_mov_y();
      void update_position(uint8_t w, uint8_t h);
      bool is_dead();
      ~Player(); 
      LinkedList* get_player();
      void set_died();
      int16_t get_x();
      int16_t get_y();
      void head_tail_collision();
      void set_dir(Directions dir);
      void set_pos(int16_t x, int16_t y);    

      // for tests
      Node* get_head();
      Node* get_tail();
      uint8_t get_score_step();
      Directions get_dir();
      vec2 get_old_tail_pos();
      void mov_body();

    protected:
      uint32_t last_tick = 0;
      
      uint16_t score=0;
      uint8_t score_step=100;
     
      Directions dir = UP;
      int8_t mov_x=0;
      int8_t mov_y=0;
      
      LinkedList* player = new LinkedList;
      Node* head = nullptr;
      Node* tail = nullptr;
      vec2 old_tail_pos;  

      bool died=false;
      void update_size();
      
      void add_body_part(int16_t x, int16_t y);
      Node* create_body_part(int16_t x, int16_t y);
      bool passed_debounce_time();
  };
  
};

