import random

from . import level
from . import point
from . import tasks
from . import tile

class Game:
    """ The game state.

    Member:
    creature -- List of creatures (list).
    level -- The game level (data.level).
    tasks -- The task list (data.tasks).
    tile_x -- The size of the map in x direction (int).
    tile_y -- The size of the map in y direction (int).
    world -- Non-dynamic world objects (list).
    """

    def __init__(self):
        self.creatures = []
        self.level = level.Level()
        self.tasks = tasks.TaskList()
        self.tile_x = 100
        self.tile_y = 100
        self.world = []

    def free_rand_pos(self):
        pos = self.rand_pos()
        while pos in self.level and self.level[pos] is not tile.PLAIN:
            pos = self.rand_pos()
        return pos

    def rand_pos(self):
        x = random.randint(0, self.tile_x - 1)
        y = random.randint(0, self.tile_y - 1)
        return point.Point(x, y)
