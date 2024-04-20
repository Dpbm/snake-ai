#include <cstdint>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../game/board.h"
#include "../game/players/player.h"

using Game::Board;
using Players::Player;
using Players::Directions;

namespace {
  TEST(CreationTest, CreateDefaultBoardTest){
    Board b{2,2};
    Player p{0, 0, Directions::RIGHT};

    b.add_player(&p);
    b.set_food_pos(0, 1);
    uint8_t** board = b.get_board();

    ASSERT_EQ(board[0][0], 1);
    ASSERT_EQ(board[0][1], 2);
    ASSERT_EQ(board[1][0], 0);
    ASSERT_EQ(board[1][1], 0);
  }

  TEST(UpdateTest, UpdatedPlayerPosTest){
    Board b{2,2};
    
    Player p{0, 0, Directions::RIGHT};
    b.add_player(&p);
    
    b.set_food_pos(1, 0);
   
    p.set_last_tick();
    b.update_player_pos();

    uint8_t** board = b.get_board();

    ASSERT_EQ(board[0][0], 0);
    ASSERT_EQ(board[0][1], 1);
    ASSERT_EQ(board[1][0], 2);
    ASSERT_EQ(board[1][1], 0);
  }

  TEST(UpdateTest, CatchFoodTest){
    Board b{2,2};
    
    Player p{0, 0, Directions::RIGHT};
    b.add_player(&p);
    
    b.set_food_pos(0,1);
  
    ASSERT_EQ(p.get_score(), 0);

    p.set_last_tick();
    b.update_player_pos();
    ASSERT_FALSE(p.is_dead());

    ASSERT_EQ(p.get_score(), 1);
  }
  
  TEST(UpdateTest, DieTest){
    Board b{2,2};
    
    Player p{0, 1, Directions::RIGHT};
    b.add_player(&p);
    
    b.set_food_pos(0,1);
  
    ASSERT_FALSE(p.is_dead());

    p.set_last_tick();
    b.update_player_pos();
    ASSERT_TRUE(p.is_dead());
  }
 
  TEST(ValueTest, BorderCollisionFalseTest){
    Board b{2,2};
    Player p{0, 1, Directions::RIGHT};
    b.add_player(&p);
    b.set_food_pos(0,1);
    b.check_border_collision();
    ASSERT_FALSE(p.is_dead());
  }
  
  TEST(ValueTest, BorderCollisionRightTest){
    Board b{2,2};
    Player p{0, 2, Directions::RIGHT};
    b.add_player(&p);
    b.set_food_pos(0,1);
    b.check_border_collision();
    ASSERT_TRUE(p.is_dead());
  }

  TEST(ValueTest, BorderCollisionLeftTest){
    Board b{2,2};
    Player p{0, -1, Directions::RIGHT};
    b.add_player(&p);
    b.set_food_pos(0,1);
    b.check_border_collision();
    ASSERT_TRUE(p.is_dead());
  }
  
  TEST(ValueTest, BorderCollisionTopTest){
    Board b{2,2};
    Player p{-1, 0, Directions::RIGHT};
    b.add_player(&p);
    b.set_food_pos(0,1);
    b.check_border_collision();
    ASSERT_TRUE(p.is_dead());
  }
  
  TEST(ValueTest, BorderCollisionDownTest){
    Board b{2,2};
    Player p{2, 0, Directions::RIGHT};
    b.add_player(&p);
    b.set_food_pos(0,1);
    b.check_border_collision();
    ASSERT_TRUE(p.is_dead());
  }
}
