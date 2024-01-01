#ifndef PLAYER
#define PLAYER

namespace Players {
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

    private:
      unsigned int x, y;
      unsigned int score = 0;
      unsigned int score_step = 100;
      unsigned int max_score = 10000;
      unsigned int size = 1;
      int mov_x = 0;
      int mov_y = 0;
      int last_tick;
      void randomize_position();
      void update_size();
  };
};

#endif // !PLAYER
