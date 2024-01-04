#ifndef PLAYER
#define PLAYER

#include "body_part.h"

namespace Players {
  
  struct Node{
    BodyParts::BodyPart *value;
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
      Players::LinkedList* get_body();
      bool is_game_over();

    private:
      unsigned int x, y;
      unsigned int score = 0;
      unsigned int score_step = 100;
      unsigned int max_score = 10000;
      unsigned int size = 1;
      int mov_x = 0;
      int mov_y = 0;
      int last_tick;
      Players::LinkedList* player = new Players::LinkedList;
      Players::Node* head = nullptr;
      Players::Node* tail = nullptr;
      bool game_over;
      void randomize_position();
      void update_size();
      Players::Node* create_body_part(unsigned int x, unsigned int y);
      void add_body_part(unsigned int x, unsigned int y);
      void check_game_over();
      bool border_head_collision();
      bool head_tail_collision();
  };
  
};

#endif // !PLAYER
