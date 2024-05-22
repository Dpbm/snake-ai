from random import choice, randint
import numpy as np
from copy import deepcopy
from .position import Position
from .directions import Directions
from qubo import qubo

class Player(Position):
    def __init__(self, P):
        super().__init__()

        self._score = 0
        self._representation = 1
        self._dir = choice(list(Directions))
        self._P = P


        self._last_pos = [self._x, self._y]
        self._body = [[self._x, self._y]]

    def update_score(self):
        self._body.append(self._last_pos)
        self._score += 1

    @property
    def body(self):
        return self._body

    @property
    def score(self):
        return self._score

    def move(self, x_bound, y_bound, fx, fy):
        qubo_result = self._get_qubo_result(fx, fy, x_bound, y_bound)

        match qubo_result:
            case '001': #'down/right'
                self._move_down_right()
            case '010': #'up/left'
                self._move_up_left()
            case '100':#'forward'
                self._move_forward()
            case _:
                raise Exception("Invalid movement")

        self._update_body()

    def _update_body(self):
        self._last_pos = deepcopy(self._body[0])

        if(len(self._body) == 1):
            self._body[0] = [self._x, self._y]
        else:
            tmp = deepcopy(self._body)
            for pos in range(1,len(self._body)):
                self._body[pos] = tmp[pos-1]
            self._body[0] = [self._x, self._y]


    def _get_qubo_result(self, fx, fy, x_bound, y_bound):
        Q = np.zeros((3,3), dtype=np.float16)
        x0 = x1 = x2 = 0
        
        match self._dir:
            case Directions.RIGHT:
                x0,x1,x2 = self._get_dir_right_data(fx, fy, x_bound, y_bound)
            case Directions.LEFT:
                x0,x1,x2 = self._get_dir_left_data(fx, fy, x_bound, y_bound)
            case Directions.UP:
                x0,x1,x2 = self._get_dir_up_data(fx, fy, x_bound, y_bound)
            case Directions.DOWN:
                x0,x1,x2 = self._get_dir_down_data(fx, fy, x_bound, y_bound)
            case _:
                raise Exception("Invalid Direction!")
        
        Q[0][0] = x0
        Q[1][1] = x1
        Q[2][2] = x2

        return qubo(Q, self._P)

    def _calculate_distance(self, fx, fy, px, py):
        dx = fx - px
        dy = fy - py
        return np.sqrt(dx**2 + dy**2)

    def _get_dir_right_data(self, fx, fy, x_bound, y_bound):
        x0 = x1 = x2 = 0

        if(self._at_the_right_wall(y_bound)):
            x0 = 1000
        else:
            x0 = self._calculate_distance(fx,fy,self._x, self._y+1)

        if(self._at_the_top_wall()):
            x1 = 1000
        else:
            x1 = self._calculate_distance(fx,fy,self._x-1, self._y)

        if(self._at_the_bottom_wall(x_bound)):
            x2 = 1000
        else:
            x2 = self._calculate_distance(fx,fy,self._x+1, self._y)

        return x0,x1,x2

    def _get_dir_left_data(self, fx, fy, x_bound, y_bound):
        x0 = x1 = x2 = 0

        
        if(self._at_the_left_wall()):
            x0 = 1000
        else:
            x0 = self._calculate_distance(fx,fy,self._x, self._y-1)

        if(self._at_the_top_wall()):
            x1 = 1000
        else:
            x1 = self._calculate_distance(fx,fy,self._x-1, self._y)

        if(self._at_the_bottom_wall(x_bound)):
            x2 = 1000
        else:
            x2 = self._calculate_distance(fx,fy,self._x+1, self._y)

        return x0,x1,x2

    def _get_dir_down_data(self, fx, fy, x_bound, y_bound):
        x0 = x1 = x2 = 0

        
        if(self._at_the_bottom_wall(x_bound)):
            x0 = 1000
        else:
            x0 = self._calculate_distance(fx,fy,self._x+1, self._y)

        if(self._at_the_left_wall()):
            x1 = 1000
        else:
            x1 = self._calculate_distance(fx,fy,self._x, self._y-1)

        if(self._at_the_right_wall(y_bound)):
            x2 = 1000
        else:
            x2 = self._calculate_distance(fx,fy,self._x, self._y+1)

        return x0,x1,x2

    def _get_dir_up_data(self, fx, fy, x_bound, y_bound):
        x0 = x1 = x2 = 0

        
        if(self._at_the_top_wall()):
            x0 = 1000
        else:
            x0 = self._calculate_distance(fx,fy,self._x-1, self._y)

        if(self._at_the_left_wall()):
            x1 = 1000
        else:
            x1 = self._calculate_distance(fx,fy,self._x, self._y-1)

        if(self._at_the_right_wall(y_bound)):
            x2 = 1000
        else:
            x2 = self._calculate_distance(fx,fy,self._x, self._y+1)

        return x0,x1,x2


    def _at_the_right_wall(self, y_bound):
        return self._y == y_bound-1
        
    def _at_the_top_wall(self):
        return self._x == 0

    def _at_the_bottom_wall(self, x_bound):
        return self._x == x_bound-1

    def _at_the_left_wall(self):
        return self._y == 0

    def _move_down_right(self):
        match self._dir:
            case Directions.RIGHT | Directions.LEFT:
                self._x += 1
                self._dir = Directions.DOWN
            case Directions.UP | Directions.DOWN:
                self._y += 1
                self._dir = Directions.RIGHT
            case _:
                raise Exception("Invalid down|right movement")
                
    def _move_up_left(self):
        match self._dir:
            case Directions.RIGHT | Directions.LEFT:
                self._x -= 1
                self._dir = Directions.UP
            case Directions.UP | Directions.DOWN:
                self._y -= 1
                self._dir = Directions.LEFT
            case _:
                raise Exception("Invalid up|left movement")

    def _move_forward(self):
        match self._dir:
            case Directions.RIGHT:
                self._y += 1
            case Directions.LEFT:
                self._y -= 1
            case Directions.UP:
                self._x -= 1
            case Directions.DOWN:
                self._x += 1
            case _:
                raise Exception("Invalid forward movement")

    
