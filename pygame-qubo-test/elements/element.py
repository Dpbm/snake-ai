from random import randint
from ..utils.constants import BOARD_W, BOARD_H


class Element:
    def __init__(self):
        self.randomize()

    def randomize(self):
        self._x = randint(0, BOARD_W)
        self._y = randint(0, BOARD_H)

    @property
    def x(self):
        return self._x

    @property
    def y(self):
        return self._y

