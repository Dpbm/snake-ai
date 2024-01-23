#pragma once
namespace BodyParts{
  class BodyPart{
    public:
      BodyPart(unsigned int x, unsigned int y);
      void update_position(unsigned int x, unsigned int y);
      unsigned int get_x();
      unsigned int get_y();

    private:
      unsigned int x,y;
  };
};
