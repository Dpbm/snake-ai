import unittest
from elements.position import Position
from elements.food import Food
from elements.directions import Directions
from elements.board import Board
from elements.player import Player

class TestElements(unittest.TestCase):
    def test_position(self):
        p = Position()

        self.assertEqual(p.representation, 0)
        self.assertEqual(p.x, 0)
        self.assertEqual(p.y, 0)

        p.randomize(10, 10)
        self.assertGreaterEqual(p.x, 0)
        self.assertLessEqual(p.x, 9)
        self.assertGreaterEqual(p.y, 0)
        self.assertLessEqual(p.y, 9)

    def test_food(self):
        f = Food()

        self.assertEqual(f.representation, 2)
        self.assertEqual(f.x, 0)
        self.assertEqual(f.y, 0)

        f.randomize(10, 10)
        self.assertGreaterEqual(f.x, 0)
        self.assertLessEqual(f.x, 9)
        self.assertGreaterEqual(f.y, 0)
        self.assertLessEqual(f.y, 9)


    def test_board_creation(self):
        b = Board(10, 3)
        self.assertEqual(b.height, 10)
        self.assertEqual(b.width, 3)
        self.assertEqual(b.score, 0)

    def test_board_step(self):
        b = Board(10, 2)
        b.player._dir = Directions.RIGHT
        b.player._x = 0
        b.player._y = 0
        b.food._x = 0
        b.food._y = 1
        b.step()
        self.assertEqual(b.score, 1)
    
    def test_board_game_over_top_collision(self):
        b = Board(10, 2)
        b.player._x = -1
        b.player._y = 0
        self.assertTrue(b.game_over())
    
    def test_board_game_over_bottom_collision(self):
        b = Board(10, 2)
        b.player._x = 10
        b.player._y = 0
        self.assertTrue(b.game_over())
    
    def test_board_game_over_left_collision(self):
        b = Board(10, 2)
        b.player._x = 0
        b.player._y = -1
        self.assertTrue(b.game_over())
    
    def test_board_game_over_right_collision(self):
        b = Board(10, 2)
        b.player._x = 0
        b.player._y = 2
        self.assertTrue(b.game_over())
    
    def test_board_game_body_collision(self):
        b = Board(10, 10)
        b.player._dir = Directions.RIGHT
        b.player._x = 0
        b.player._y = 0

        b.player.update_score()
        b.player._move_forward()
        b.player.update_score()
        b.player._move_forward()
        b.player.update_score()
        b.player._move_down_right()
        b.player._move_up_left()
        b.player._move_forward()

        self.assertTrue(b.game_over())
    
    def test_player_creation(self):
        p = Player(10)
        self.assertEqual(p.head[0],0)
        self.assertEqual(p.head[1],0)
        self.assertEqual(p.score, 0)
        self.assertEqual(p.representation, 1)

    def test_player_update_score(self):
        p = Player(10)
        p.update_score()
        self.assertEqual(p.score, 1)
        self.assertEqual(len(p.body),2)
    
    def test_player_move(self):
        p = Player(10)
        p._x = 0
        p._y = 0
        p._dir = Directions.RIGHT
        
        p.move(10, 10, 1, 0)
        self.assertEqual(p.head[0], 1)
        self.assertEqual(p.head[1], 0)


if __name__ == '__main__':
    unittest.main()
