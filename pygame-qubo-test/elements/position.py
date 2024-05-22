from random import randint


class Position:
    def __init__(self):
        self._x = 0
        self._y = 0
        self._representation = 0

    def randomize(self, max_x, max_y):
        self._x = randint(0, max_x-1)
        self._y = randint(0, max_y-1)

    @property
    def x(self):
        return self._x

    @property
    def y(self):
        return self._y

    @property
    def representation(self):
        return self._representation

