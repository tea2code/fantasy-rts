#from ai import pathfinding
from config import basereader
from data.world import block, point, region
from ui import graphics

if __name__ == '__main__':
    import doctest
    # TODO doctest.testmod(pathfinding)
    doctest.testmod(basereader)
    doctest.testmod(point)
    doctest.testmod(region)
    doctest.testmod(graphics)
    doctest.testmod(block)