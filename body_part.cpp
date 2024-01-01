#include "body_part.h"

namespace BodyParts{
  unsigned int x,y;

  BodyPart::BodyPart(unsigned int x, unsigned int y){
    this->x = x;
    this->y = y;
  }

  void BodyPart::update_position(unsigned int x, unsigned int y){
    this->x = x;
    this->y = y;
  }

  unsigned int BodyPart::get_x(){
    return this->x;
  }
  
  unsigned int BodyPart::get_y(){
    return this->y;
  }
}
