#pragma once

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

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
      bool collision(unsigned int food_x, unsigned int food_y);
      void update_score();
      unsigned int get_x();
      unsigned int get_y();
      unsigned int get_score();
      unsigned int get_size();
      int get_mov_x();
      int get_mov_y();
      void update_position();
      bool is_die();
      ~Player(); 
      void render(SDL_Renderer* render);
      void randomize_position();
      void set_score_step(uint8_t score_step);
      void set_max_score(uint16_t max_score);

    private:
      unsigned int x, y;
      unsigned int score=0;
      unsigned int score_step=100;
      unsigned int max_score=10000;
      unsigned int size = 1;
      int mov_x=0;
      int mov_y=0;
      int last_tick;
      LinkedList* player = new LinkedList;
      Node* head = nullptr;
      Node* tail = nullptr;
      bool died=false;
      void update_size();
      Node* create_body_part(unsigned int x, unsigned int y);
      void add_body_part(unsigned int x, unsigned int y);
      void check_died();
      bool border_head_collision();
      bool head_tail_collision();
  };
  
};

