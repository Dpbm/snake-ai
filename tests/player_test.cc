#include <cstdint>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../game/players/player.h"
#include "../helpers/constants.h"

using ::testing::AllOf;
using ::testing::Ge;
using ::testing::Le;
using Players::Player;
using Players::Directions;

namespace {
  TEST(CreationTest, CreateEmptyPlayerTest){
    Player p = Player();

    ASSERT_EQ(p.get_score(), 0);
    ASSERT_EQ(p.get_mov_x(), 0);
    ASSERT_EQ(p.get_mov_y(), 0);
    ASSERT_EQ(p.get_score_step(), 100);
    ASSERT_NE(p.get_player(), nullptr);
    ASSERT_EQ(p.get_head(), nullptr);
    ASSERT_EQ(p.get_tail(), nullptr);
    ASSERT_EQ(p.get_dir(), Directions::UP);
  }
  
  TEST(CreationTest, CreatePlayerTest){
    Player p = Player(2, 1, 1);

    ASSERT_EQ(p.get_score(), 0);
    ASSERT_THAT(p.get_mov_x(), AllOf(Ge(-1), Le(1)));
    ASSERT_THAT(p.get_mov_y(), AllOf(Ge(-1), Le(1)));
    ASSERT_EQ(p.get_score_step(), 2);
    ASSERT_NE(p.get_player(), nullptr);
    ASSERT_NE(p.get_head(), nullptr);
    ASSERT_NE(p.get_tail(), nullptr);
    ASSERT_EQ(p.get_head(), p.get_tail());
    ASSERT_THAT((int)p.get_dir(), AllOf(Ge((int)Directions::UP), Le((int)Directions::RIGHT)));
  }

  TEST(UpdateTest, UpdatePosNoTicksPassedTest){
    Player p = Player(1, 10, 10);
    p.set_pos(0, 0);
    p.set_dir(Directions::RIGHT);
    int16_t old_x = p.get_x();
    int16_t old_y = p.get_y();

    p.update_pos();

    ASSERT_EQ(old_x, p.get_x());
    ASSERT_EQ(old_y, p.get_y());
  }
}
