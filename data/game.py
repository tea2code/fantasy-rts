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
    size_x -- The size of the map in x direction (int).
    size_y -- The size of the map in y direction (int).
    tasks -- The task list (data.tasks).
    world -- Non-dynamic world objects (list).
    """

    def __init__(self):
        self.creatures = []
        self.level = level.Level()
        self.tasks = tasks.TaskList()
        self.size_x = 100
        self.size_y = 100
        self.world = []

    def free_rand_pos(self):
        """ Returns a free random position.

        Test:
        >>> p1 = point.Point(0, 0)
        >>> p2 = point.Point(0, 1)
        >>> p3 = point.Point(1, 0)
        >>> p4 = point.Point(1, 1)
        >>> l = level.Level()
        >>> l[p1] = tile.PLAIN
        >>> l[p2] = tile.WALL
        >>> l[p3] = tile.WALL
        >>> g = Game()
        >>> g.level = l
        >>> g.size_x = 2
        >>> g.size_y = 2
        >>> fp = g.free_rand_pos()
        >>> fp == p1 or fp == p4
        True
        >>> fp = g.free_rand_pos()
        >>> fp == p1 or fp == p4
        True
        >>> fp = g.free_rand_pos()
        >>> fp == p1 or fp == p4
        True
        """
        pos = self.rand_pos()
        while pos in self.level and self.level[pos] is not tile.PLAIN:
            pos = self.rand_pos()
        return pos

    def rand_pos(self):
        """ Returns a random position on the map.

        Test:
        >>> g = Game()
        >>> g.size_x = 2
        >>> g.size_y = 2
        >>> p = g.rand_pos()
        >>> 0 <= p.x < 2 and 0 <= p.y < 2
        True
        >>> 0 <= p.x < 2 and 0 <= p.y < 2
        True
        >>> 0 <= p.x < 2 and 0 <= p.y < 2
        True
        >>> 0 <= p.x < 2 and 0 <= p.y < 2
        True
        """
        x = random.randint(0, self.size_x - 1)
        y = random.randint(0, self.size_y - 1)
        return point.Point(x, y)

if __name__ == '__main__':
    print('Executing doctest.')
    import doctest
    doctest.testmod()