#pragma once

#include <cstdint>
#include "../helpers/utils.h"
#include "./players/player.h"

using Utils::vec2;
using Players::Player;

namespace Game {
  class Board{
    public:
      Board(uint8_t w, uint8_t h);
      uint8_t** get_board();
      uint8_t get_width();
      uint8_t get_height();
      
      vec2 get_food();
      void random_food();
      void set_food_pos(int16_t x, int16_t y);
      
      void update_player_pos();
      void check_border_collision();
      
      void add_player(Player* player);
      bool get_caught_the_food();
      
      ~Board();

    private:
      uint8_t w, h;
      uint8_t** board;
      vec2 food;
      Player* player;
      void clear_board();
      bool caught_the_food = false;
  };
}
