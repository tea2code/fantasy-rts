from data.world import block, tile
from data.world.point import Factory as PointFactory
from world import regiongenerator

class AllGrassRegionGenerator(regiongenerator.RegionGenerator):
    """ Test region generator which only returns grass blocks.

    Member.
    _map -- The pregenerated map (dict).
    """

    def __init__(self, size_x, size_y):
        self._map = {}
        for x in range(size_x):
            for y in range(size_y):
                self._map[PointFactory.new_point(x, y, 0)] = self.__grass_block()

    def all_blocks(self, z_level):
        return self._map

    def new_block(self, pos):
        return self._map[pos]

    def __grass_block(self):
        t = tile.Tile('grass')
        b = block.Block()
        b._insert_tile(t)
        return b