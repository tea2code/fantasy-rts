from data import creature
from data import level
from data import point
from data import tile

class Demo:
    """ Creates a repeatable demo game.

    Member:
    data -- The data object (data.data).
    """

    def __init__(self, data):
        self.data = data

    def load(self, size):
        """ Loads the game into the data object. """
        # Create level map.
        size_half = int(size / 2)
        size_quarter = int(size / 4)
        offset = 5
        lvl = level.Level()
        for x in range(size):
            lvl[point.Point(x, 0)] = tile.WALL
            lvl[point.Point(x, size - 1)] = tile.WALL
        for y in range(size):
            lvl[point.Point(0, y)] = tile.WALL
            lvl[point.Point(size - 1, y)] = tile.WALL
        for x in range(size_quarter, size_half + size_quarter):
            lvl[point.Point(x, size_quarter - offset)] = tile.WALL
            lvl[point.Point(x, size_half + size_quarter + offset)] = tile.WALL
        for y in range(size_quarter, size_half + size_quarter):
            lvl[point.Point(size_quarter - offset, y)] = tile.WALL
            lvl[point.Point(size_half + size_quarter + offset, y)] = tile.WALL
        self.data.game.level = lvl

        # Add creatures.
        num_x = 10
        num_y = num_x
        for x in range(1, num_x):
            for y in range(1, num_y):
                c = creature.Creature()
                c.pos = point.Point(x, y)
                self.data.game.creatures.append(c)
                self.data.dirty_pos.add(c.pos)