from . import dynamicentity, staticentity

class Region:
    """ Represents a region in the world. A region is a map the player is
    currently on. The map consists of a 3 dimensional cube split into positions
    representing a single block.

    Member:
    region_generator -- The region generator behind the region (world.regiongenerator).
    _entity_pos -- Maps entities to their exact positions (dict).
    _pos_block -- Maps positions to the block on this position (dict).
    """

    def __init__(self, region_generator):
        self.region_generator = region_generator
        self._entity_pos = {}
        self._pos_block = {}

    def get_block(self, pos):
        """ Returns the block at the given position.

        Test:
        >>> from data.world import entity
        >>> e = entity.Entity('id')
        >>> from data.world import point
        >>> p = point.Point()
        >>> from test import regiongenerator
        >>> rg = regiongenerator.AllGrassRegionGenerator(2, 2)
        >>> r = Region(rg)
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
        >>> r = Region(rg)
        >>> r.get_pos(e) # doctest: +ELLIPSIS
        Traceback (most recent call last):
        ...
        KeyError: ...
        >>> r.set_pos(e, p)
        >>> r.get_pos(e) is p
        True
        """
        return self._entity_pos[entity]

    def remove_entity(self, entity):
        """ Removes an entity.

        Test:
        >>> from data.world import entity
        >>> e = entity.Entity('id')
        >>> from data.world import point
        >>> p = point.Point()
        >>> from test import regiongenerator
        >>> rg = regiongenerator.AllGrassRegionGenerator(2, 2)
        >>> r = Region(rg)
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