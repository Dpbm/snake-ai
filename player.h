#ifndef PLAYER
#define PLAYER

namespace Players {
  class Player{
    public:
      Player();
      Player(unsigned int score_step);
      void move_up();
      void move_down();
      void move_left();
      void move_right();
      bool collision(unsigned int food_x, unsigned int food_y);
      void update_score();
      unsigned int get_x();
      unsigned int get_y();
      unsigned int get_score();

    private:
      unsigned int x, y;
      unsigned int score = 0;
      unsigned int score_step = 100;
  };
};

#endif // !PLAYER
