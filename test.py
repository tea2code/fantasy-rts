from ai import pathfinding
from config import basereader
from data import game
from data.world import block, point
from ui import graphics

if __name__ == '__main__':
    import doctest
    doctest.testmod(pathfinding)
    doctest.testmod(basereader)
    doctest.testmod(game)
    doctest.testmod(point)
    doctest.testmod(graphics)
    doctest.testmod(block)