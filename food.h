#ifndef FOOD
#define FOOD

namespace Foods {
  class Food{
    public:
      Food();
      unsigned int get_x();
      unsigned int get_y();

    private:
      unsigned int x, y;
  };
};


#endif // !FOOD