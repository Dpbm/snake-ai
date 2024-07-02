#include <gtest/gtest.h>
#include "../game/players/player.h"
#include "../game/players/qubo_player.h"
#include "../helpers/utils.h"

using Players::Directions;
using Players::QuboPlayer;
using Utils::vec2;

namespace {

  TEST(ValueTest, NextMovRightTest){
    QuboPlayer p{10, 10};
    p.set_dir(Directions::UP);
    p.set_pos(2, 3);

    vec2 food{7, 3};
    p.next_mov(food);
    ASSERT_EQ(p.get_dir(), Directions::RIGHT);
  }
  
  TEST(ValueTest, NextMovUpTest){
    QuboPlayer p{10, 10};
    p.set_dir(Directions::RIGHT);
    p.set_pos(5, 5);

    vec2 food{1, 5};
    p.next_mov(food);
    ASSERT_EQ(p.get_dir(), Directions::UP);
  }

  TEST(ValueTest, NextMovDownTest){
    QuboPlayer p{10, 10};
    p.set_dir(Directions::LEFT);
    p.set_pos(5, 5);

    vec2 food{6, 5};
    p.next_mov(food);
    ASSERT_EQ(p.get_dir(), Directions::DOWN);
  }
  
  TEST(ValueTest, NextMovLeftTest){
    QuboPlayer p{10, 10};
    p.set_dir(Directions::UP);
    p.set_pos(5, 5);

    vec2 food{5, 1};
    p.next_mov(food);
    ASSERT_EQ(p.get_dir(), Directions::LEFT);
  }
}
