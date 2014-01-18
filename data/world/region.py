import random

from . import dynamicentity, staticentity
from .point import Factory as PointFactory

class Region:
    """ Represents a region in the world. A region is a map the player is
    currently on. The map consists of a 3 dimensional cube split into positions
    representing a single block.

    Member:
    region_generator -- The region generator behind the region (world.regiongenerator).
    size_x -- The size of the map in x direction (int).
    size_y -- The size of the map in y direction (int).
    _entity_pos -- Maps entities to their exact positions (dict).
    _pos_block -- Maps positions to the block on this position (dict).
    """

    def __init__(self, region_generator, size_x, size_y):
        self.region_generator = region_generator
        self.size_x = size_x
        self.size_y = size_y
        self._entity_pos = {}
        self._pos_block = {}

    def free_neighbors(self, pos, blocked):
        """ Returns free neighbors of given position.

        >>> from data.world import tile
        >>> t = tile.Tile('id')
        >>> t.blocking = ['block']
        >>> from data.world import point
        >>> p = point.Point(1, 0)
        >>> from test import regiongenerator
        >>> rg = regiongenerator.AllGrassRegionGenerator(2, 2)
        >>> r = Region(rg, 2, 2)
        >>> r.set_pos(t, p)
        >>> r.free_neighbors(point.Point(0, 0), ['block']) == [point.Point(0, 1)]
        True
        >>> r.free_neighbors(point.Point(0, 1), ['block']) == [point.Point(0, 0), point.Point(1, 1)]
        True
        """
        neighbors = self.neighbors(pos)
        result = []
        for neighbor in neighbors:
            if not self.get_block(neighbor).is_blocking(blocked):
                result.append(neighbor)
        return result

    def free_random_pos(self, blocked, z_level=None):
        """ Finds a random position which is free according to the given
        blocked list. If z-level is set the position is on this level else it
        can be everywhere.

        Test:
        >>> from data.world import tile
        >>> t1 = tile.Tile('id')
        >>> t1.blocking = ['block']
        >>> t2 = tile.Tile('id')
        >>> t2.blocking = ['block']
        >>> from data.world import point
        >>> p1 = point.Point(0, 0)
        >>> p2 = point.Point(0, 1)
        >>> p3 = point.Point(1, 0)
        >>> p4 = point.Point(1, 1)
        >>> from test import regiongenerator
        >>> rg = regiongenerator.AllGrassRegionGenerator(2, 2)
        >>> r = Region(rg, 2, 2)
        >>> r.set_pos(t1, p2)
        >>> r.set_pos(t2, p3)
        >>> fp = r.free_random_pos(['block'], 0)
        >>> fp == p1 or fp == p4
        True
        >>> fp = r.free_random_pos(['block'], 0)
        >>> fp == p1 or fp == p4
        True
        >>> fp = r.free_random_pos(['block'], 0)
        >>> fp == p1 or fp == p4
        True
        """
        pos = self.random_pos(z_level)
        while self.get_block(pos).is_blocking(blocked):
            pos = self.random_pos(z_level)
        return pos

    def get_block(self, pos):
        """ Returns the block at the given position.

        Test:
        >>> from data.world import entity
        >>> e = entity.Entity('id')
        >>> from data.world import point
        >>> p = point.Point()
        >>> from test import regiongenerator
        >>> rg = regiongenerator.AllGrassRegionGenerator(2, 2)
        >>> r = Region(rg, 2, 2)
        >>> b = r.get_block(p)
        >>> b.get_tiles()[0].id
        'entity.tile.grass'
        """
        if pos not in self._pos_block:
            self._pos_block[pos] = self.region_generator.new_block(pos)
        return self._pos_block[pos]

    def get_pos(self, entity):
        """ Returns the exact position of the given entity.

        Test:
        >>> from data.world import entity
        >>> e = entity.Entity('id')
        >>> from data.world import point
        >>> p = point.Point()
        >>> from test import regiongenerator
        >>> rg = regiongenerator.AllGrassRegionGenerator(2, 2)
        >>> r = Region(rg, 2, 2)
        >>> r.get_pos(e) # doctest: +ELLIPSIS
        Traceback (most recent call last):
        ...
        KeyError: ...
        >>> r.set_pos(e, p)
        >>> r.get_pos(e) is p
        True
        """
        return self._entity_pos[entity]

    def neighbors(self, pos):
        """ Returns a list of all neighbors for the given position.

        Test:
        >>> from data.world import point
        >>> from test import regiongenerator
        >>> rg = regiongenerator.AllGrassRegionGenerator(3, 3)
        >>> r = Region(rg, 3, 3)
        >>> r.neighbors(point.Point(0, 0)) == [point.Point(1, 0), point.Point(0, 1)]
        True
        >>> r.neighbors(point.Point(1, 1)) == [point.Point(1, 0), point.Point(0, 1), point.Point(2, 1), point.Point(1, 2)]
        True
        >>> r.neighbors(point.Point(2, 2)) == [point.Point(2, 1), point.Point(1, 2)]
        True
        """
        result = []
        # TODO Up
        # TODO Down
        # Top
        if pos.y - 1 >= 0:
            result.append(PointFactory.new_point(pos.x, pos.y - 1))
        # Left
        if pos.x - 1 >= 0:
            result.append(PointFactory.new_point(pos.x - 1, pos.y))
        # Right
        if pos.x + 1 < self.size_x:
            result.append(PointFactory.new_point(pos.x + 1, pos.y))
        # Bottom
        if pos.y + 1 < self.size_y:
            result.append(PointFactory.new_point(pos.x, pos.y + 1))
        return result

    def random_pos(self, z_level=None):
        """ Returns a random position on the map. If z-level is set the position
        is on this level else it can be everywhere.

        Test:
        >>> from test import regiongenerator
        >>> rg = regiongenerator.AllGrassRegionGenerator(2, 2)
        >>> r = Region(rg, 2, 2)
        >>> p = r.random_pos(0)
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
        if z_level is None:
            z_level = 0 # TODO Select random z-level.
        return PointFactory.new_point(x, y, z_level)

    def remove_entity(self, entity):
        """ Removes an entity.

        Test:
        >>> from data.world import entity
        >>> e = entity.Entity('id')
        >>> from data.world import point
        >>> p = point.Point()
        >>> from test import regiongenerator
        >>> rg = regiongenerator.AllGrassRegionGenerator(2, 2)
        >>> r = Region(rg, 2, 2)
        >>> r.set_pos(e, p)
        >>> r.get_pos(e) is p
        True
        >>> r.remove_entity(e)
        >>> r.get_pos(e) # doctest: +ELLIPSIS
        Traceback (most recent call last):
        ...
        KeyError: ...
        """
        # Remove from block.
        pos = self.get_pos(entity)
        block = self.get_block(pos)
        if isinstance(entity, staticentity.StaticEntity):
            block.remove_static(entity)
        elif isinstance(entity, dynamicentity.DynamicEntity):
            block.remove_dynamic(entity)
        else:
            block.remove_tile(entity)

        # Remove from entity dict.
        del self._entity_pos[entity]

    def set_pos(self, entity, pos):
        """ Sets the entity to the given position.

        Test: See get_pos().
        """
        # Remove from block if exists.
        if entity in self._entity_pos:
            self.remove_entity(entity)

        # Insert in block.
        block = self.get_block(pos)
        if isinstance(entity, staticentity.StaticEntity):
            block.insert_static(entity)
        elif isinstance(entity, dynamicentity.DynamicEntity):
            block.insert_dynamic(entity)
        else:
            block.insert_tile(entity)

        # Insert in entity dict.
        self._entity_pos[entity] = pos

if __name__ == '__main__':
    print('Executing doctest.')
    import doctest
    doctest.testmod()