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
      Player(uint8_t score_step, uint16_t max_score, uint8_t board_w, uint8_t board_h);
      void random_pos(uint8_t w, uint8_t h);
      void random_dir();
      void update_pos();
      void direction_up();
      void direction_down();
      void direction_left();
      void direction_right();
      void update_score();
      unsigned int get_score();
      void reset_score();
      unsigned int get_size();
      int8_t get_mov_x();
      int8_t get_mov_y();
      void update_position(uint8_t w, uint8_t h);
      bool is_dead();
      ~Player(); 
      void set_score_step(uint8_t score_step);
      void set_max_score(uint16_t max_score);
      LinkedList* get_player();
      void set_died();

      uint32_t last_tick = 0;
      int16_t get_x();
      int16_t get_y();
      void head_tail_collision();

    private:
      unsigned int score=0;
      unsigned int score_step=100;
      unsigned int max_score=10000;
      unsigned int size = 1;
     
      Directions dir;
      int8_t mov_x=0;
      int8_t mov_y=0;
      
      LinkedList* player = new LinkedList;
      Node* head = nullptr;
      Node* tail = nullptr;
      
      bool died=false;
      void update_size();
      
      void add_body_part(int16_t x, int16_t y);
      Node* create_body_part(int16_t x, int16_t y);
      
  };
  
};

