import random

from data.config import ID
from data.world import block, factory
from data.world.point import Factory as PointFactory
from world import regiongenerator

class FlatRegionGenerator(regiongenerator.RegionGenerator):
    """ Implementation of the region generator which creates always the same
    flat map for z-level 0.

    Member:
    _map -- The pregenerated map for z-level 0 (dict).
    """

    def __init__(self, data):
        size_x = data.game.size_x
        size_y = data.game.size_y

        size_x_half = int(size_x / 2)
        size_x_quarter = int(size_x / 4)
        size_y_half = int(size_y / 2)
        size_y_quarter = int(size_y / 4)
        offset = 5

        self._map = {}

        # Initialize everything with grass.
        for x in range(size_x):
            for y in range(size_y):
                self._map[PointFactory.new_point(x, y)] = self.__grass_block(data)

        # Border.
        for x in range(size_x):
            self._map[PointFactory.new_point(x, 0)] = self.__wall_block(data)
            self._map[PointFactory.new_point(x, size_x - 1)] = self.__wall_block(data)
        for y in range(size_y):
            self._map[PointFactory.new_point(0, y)] = self.__wall_block(data)
            self._map[PointFactory.new_point(size_y - 1, y)] = self.__wall_block(data)

        # Open rectangle.
        for x in range(size_x_quarter, size_x_half + size_x_quarter):
            self._map[PointFactory.new_point(x, size_x_quarter - offset)] = self.__wall_block(data)
            self._map[PointFactory.new_point(x, size_x_half + size_x_quarter + offset)] = self.__wall_block(data)
        for y in range(size_y_quarter, size_y_half + size_y_quarter):
            self._map[PointFactory.new_point(size_y_quarter - offset, y)] = self.__wall_block(data)
            self._map[PointFactory.new_point(size_y_half + size_y_quarter + offset, y)] = self.__wall_block(data)

        # Add trees.
        for x in range(size_x):
            for y in range(size_y):
                if random.random() > 0.03:
                    continue
                point = PointFactory.new_point(x, y)
                b = self._map[point]
                e = factory.new_static_entity(data.game.wood_plant, data)
                if not b.is_blocking(e.blocked):
                    b.insert_static(e)

        # Add shrubs.
        for x in range(size_x):
            for y in range(size_y):
                if random.random() > 0.03:
                    continue
                point = PointFactory.new_point(x, y)
                b = self._map[point]
                e = factory.new_static_entity(data.game.food_plant, data)
                if not b.is_blocking(e.blocked):
                    b.insert_static(e)

    def all_blocks(self, z_level):
        return self._map

    def new_block(self, pos):
        return self._map[pos]

    def __grass_block(self, data):
        t = factory.new_tile(data.game.tile_ground, data)
        b = block.Block()
        b.insert_tile(t)
        return b

    def __wall_block(self, data):
        t = factory.new_tile(data.game.tile_wall, data)
        b = block.Block()
        b.insert_tile(t)
        return b