import numpy as np
import pygame
from .food import Food
from .player import Player

class Board:
    def __init__(self, height, width):
        self._h = height
        self._w = width
        self._food = Food()
        self._player = Player((height*width) + 10)

        self._randomize_player_food_positions()
        self._update_board()

    def _randomize_player_food_positions(self):
        self._food.randomize(self._w, self._h)
        self._player.randomize(self._w, self._h)

    def _update_board(self):
        self._board = np.zeros((self._h, self._w), dtype=np.int8)
        self._board[self._food.x][self._food.y] = self._food.representation

        for x,y in self._player.body:
            self._board[x][y] = self._player.representation

    @property
    def height(self):
        return self._h

    @property
    def width(self):
        return self._w

    @property
    def score(self):
        return self._player.score

    def step(self):
        self._player.move(self._w, self._h, self._food.x, self._food.y)

        if(self._caught_food()):
            print("[+] caught a food")
            self._food.randomize(self._w, self._h)
            self._player.update_score()

        self._update_board()

    def draw(self, screen, side):
        cell_color =  (0,0,0)
        player_color = (255, 0, 0)
        food_color = (0, 255, 0)

        colors = [cell_color, player_color, food_color]

        for i in range(self._h):
            for j in range(self._w):
                cell_type = self._board[i][j]
                color = colors[cell_type]
                pygame.draw.rect(screen, color, (i*side, j*side, side, side))
    
    def game_over(self):
        return self._player.x < 0 or self._player.x > self._h or self._player.y < 0 or self._player.y > self._w or self._player.collide_itself()

    def _caught_food(self):
        return self._player.x == self._food.x and self._food.y == self._player.y
