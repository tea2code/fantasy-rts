from ai import pathfinding
from config import basereader
from data.ai import tasklist
from data.world import block, point, region, resourcemanager
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
    doctest.testmod(resourcemanager)