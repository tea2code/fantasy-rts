from ai import pathfinding
from ai.task import tasklist
from config import basereader
from data.world import block, point, region
from ui import helper as ui_helper

if __name__ == '__main__':
    import doctest
    doctest.testmod(pathfinding)
    doctest.testmod(basereader)
    doctest.testmod(point)
    doctest.testmod(region)
    doctest.testmod(ui_helper)
    doctest.testmod(block)
    doctest.testmod(tasklist)