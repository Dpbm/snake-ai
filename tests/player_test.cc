#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../game/players/player.h"

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

  TEST(UpdateTest, UpdatePosTicksPassedTest){
    Player p{1, 0, 0, Directions::RIGHT};
    
    ASSERT_EQ(p.get_x(),0);
    ASSERT_EQ(p.get_y(),0);
    ASSERT_FALSE(p.is_dead());
    
    p.set_last_tick();
    p.update_pos();
   
    ASSERT_EQ(p.get_x(),0);
    ASSERT_EQ(p.get_y(),1);
  }

  TEST(UpdateTest, SetDirectionUpTest){
    Player p;

    ASSERT_EQ(p.get_mov_x(), 0);
    ASSERT_EQ(p.get_mov_y(), 0);
    ASSERT_EQ(p.get_dir(), Directions::UP);
    p.direction_up();
    ASSERT_EQ(p.get_mov_x(), -1);
    ASSERT_EQ(p.get_mov_y(), 0);
    ASSERT_EQ(p.get_dir(), Directions::UP);
  }
  
  TEST(UpdateTest, SetDirectionDownTest){
    Player p;

    ASSERT_EQ(p.get_mov_x(), 0);
    ASSERT_EQ(p.get_mov_y(), 0);
    ASSERT_EQ(p.get_dir(), Directions::UP);
    p.direction_down();
    ASSERT_EQ(p.get_mov_x(), 1);
    ASSERT_EQ(p.get_mov_y(), 0);
    ASSERT_EQ(p.get_dir(), Directions::DOWN);
    
  }
  
  TEST(UpdateTest, SetDirectionLeftTest){
    Player p;

    ASSERT_EQ(p.get_mov_x(), 0);
    ASSERT_EQ(p.get_mov_y(), 0);
    ASSERT_EQ(p.get_dir(), Directions::UP);
    p.direction_left();
    ASSERT_EQ(p.get_mov_x(), 0);
    ASSERT_EQ(p.get_mov_y(), -1);
    ASSERT_EQ(p.get_dir(), Directions::LEFT);
  }
  
  TEST(UpdateTest, SetDirectionRightTest){
    Player p;

    ASSERT_EQ(p.get_mov_x(), 0);
    ASSERT_EQ(p.get_mov_y(), 0);
    ASSERT_EQ(p.get_dir(), Directions::UP);
    p.direction_right();
    ASSERT_EQ(p.get_mov_x(), 0);
    ASSERT_EQ(p.get_mov_y(), 1);
    ASSERT_EQ(p.get_dir(), Directions::RIGHT);
  }

  TEST(UpdateTest, UpdateScoreTest){
    Player p{1, 0, 0, Directions::RIGHT};
    ASSERT_EQ(p.get_score(), 0);
    ASSERT_EQ(p.get_head()->next, nullptr);
    ASSERT_EQ(p.get_head(), p.get_tail());
    p.update_score();
    ASSERT_EQ(p.get_score(), 1);
    ASSERT_NE(p.get_head()->next, nullptr);
    ASSERT_NE(p.get_head(), p.get_tail());
  }

  TEST(UpdateTest, DeadTest){
    Player p;
    ASSERT_FALSE(p.is_dead());
    p.set_died();
    ASSERT_TRUE(p.is_dead());
  }

  TEST(UpdateTest, HeadTailCollisionTest){
    Player p{1, 0, 0, Directions::RIGHT};

    ASSERT_FALSE(p.is_dead());
    //y = 1
    p.set_last_tick();
    p.update_pos();
    p.update_score();

    //y = 2
    p.set_last_tick();
    p.update_pos();
    p.update_score();


    //y = 3
    p.set_last_tick();
    p.update_pos();
    p.update_score();
    
    //y = 4
    p.set_last_tick();
    p.update_pos();
    p.update_score();
    
    //y = 5
    p.set_last_tick();
    p.update_pos();
    p.update_score();

    //turn towards its tail
    p.direction_down();
    p.set_last_tick();
    p.update_pos();
    p.direction_left();
    p.set_last_tick();
    p.update_pos();
    p.direction_up();
    p.set_last_tick();
    p.update_pos();

    p.head_tail_collision();

    ASSERT_TRUE(p.is_dead());
  }
}
