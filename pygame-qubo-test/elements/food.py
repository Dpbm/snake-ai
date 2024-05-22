from .position import Position

class Food(Position):
    def __init__(self):
        super().__init__()

        self._representation = 2
