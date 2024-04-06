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
      void random_food();
      void set_food_pos(int16_t x, int16_t y);
      void add_player(Player* player);
      void update_player_pos();
      void check_border_collision();
      ~Board();

    private:
      uint8_t w, h;
      uint8_t** board;
      vec2 food;
      Player* player;
      void clear_board();
  };
}
