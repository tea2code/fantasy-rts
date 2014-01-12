import random
import time

from data import level
from data import tile
from data.world import point
from general import factory


class Demo:
    """ Creates a repeatable demo game.

    Constants:
    TIME_BURNER -- If not None the application will sleep every frame for the given time (float/None).

    Member:
    data -- The data object (data.data).
    """

    TIME_BURNER = None

    def __init__(self, data):
        self.data = data

    def load(self, size_x, size_y):
        """ Loads the game into the data object. """
        # Create level map.
        size_x_half = int(size_x / 2)
        size_x_quarter = int(size_x / 4)
        size_y_half = int(size_y / 2)
        size_y_quarter = int(size_y / 4)
        offset = 5
        lvl = level.Level()
        for x in range(size_x):
            lvl[point.Point(x, 0)] = tile.WALL
            lvl[point.Point(x, size_x - 1)] = tile.WALL
        for y in range(size_y):
            lvl[point.Point(0, y)] = tile.WALL
            lvl[point.Point(size_y - 1, y)] = tile.WALL
        for x in range(size_x_quarter, size_x_half + size_x_quarter):
            lvl[point.Point(x, size_x_quarter - offset)] = tile.WALL
            lvl[point.Point(x, size_x_half + size_x_quarter + offset)] = tile.WALL
        for y in range(size_y_quarter, size_y_half + size_y_quarter):
            lvl[point.Point(size_y_quarter - offset, y)] = tile.WALL
            lvl[point.Point(size_y_half + size_y_quarter + offset, y)] = tile.WALL
        self.data.game.level = lvl

        # Add creatures.
        num_x = 20
        num_y = num_x
        for x in range(1, num_x):
            for y in range(1, num_y):
                factory.new_creature(self.data, x, y, 0)
        random.shuffle(self.data.game.creatures)

    def tick(self, run_time, delta_time, data):
        if len(data.game.world) < 10 and run_time % 1 <= delta_time:
            # Create new shrub.
            pos = data.game.free_rand_pos()
            s = factory.new_world_entity(data, 'entity.static.berry-shrub', pos=pos)

        # Burn additional time.
        if self.TIME_BURNER:
            time.sleep(self.TIME_BURNER)