#pragma once

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <cstdint>

namespace Players {
  struct Node{
    SDL_Rect *value;
    Node* next;
  };

  typedef struct Node Node;
  typedef struct Node LinkedList;
  
  class Player{
    public:
      Player();
      Player(unsigned int score_step, unsigned int max_score);
      void direction_up();
      void direction_down();
      void direction_left();
      void direction_right();
      bool collision(int16_t food_x, int16_t food_y);
      void update_score();
      int16_t get_x();
      int16_t get_y();
      unsigned int get_score();
      void reset_score();
      unsigned int get_size();
      int8_t get_mov_x();
      int8_t get_mov_y();
      void update_position();
      bool is_dead();
      ~Player(); 
      void render(SDL_Renderer* render);
      void randomize_position();
      void set_score_step(uint8_t score_step);
      void set_max_score(uint16_t max_score);

    private:
      int16_t x, y;
      unsigned int score=0;
      unsigned int score_step=100;
      unsigned int max_score=10000;
      unsigned int size = 1;
      int8_t mov_x=0;
      int8_t mov_y=0;
      int last_tick;
      LinkedList* player = new LinkedList;
      Node* head = nullptr;
      Node* tail = nullptr;
      bool died=false;
      void update_size();
      Node* create_body_part(int16_t x, int16_t y);
      void add_body_part(int16_t x, int16_t y);
      void check_died();
      bool border_head_collision();
      bool head_tail_collision();
  };
  
};

