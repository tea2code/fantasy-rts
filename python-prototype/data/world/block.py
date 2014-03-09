class Block():
    """ A block in the world at a certain position.

    Member:
    _blocked -- Cache for is blocking test (dict).
    _dynamics -- List of dynamic entities in the block (list).
    _statics -- List of static entities in the block (list).
    _tiles -- List of tiles in the block (list).
    """

    def __init__(self):
        self._blocked = {}
        self._dynamics = []
        self._statics = []
        self._tiles = []

    def get_dynamics(self):
        """  Returns list of all dynamic entities.

        Test:
        >>> b = Block()
        >>> b.get_dynamics()
        []
        >>> b._insert_dynamic('test')
        >>> b.get_dynamics()
        ['test']
        """
        return self._dynamics

    def get_statics(self):
        """  Returns list of all static entities.

        Test:
        >>> b = Block()
        >>> b.get_statics()
        []
        >>> b._insert_static('test')
        >>> b.get_statics()
        ['test']
        """
        return self._statics

    def get_tiles(self):
        """  Returns list of all tiles.

        Test:
        >>> b = Block()
        >>> b.get_tiles()
        []
        >>> b._insert_tile('test')
        >>> b.get_tiles()
        ['test']
        """
        return self._tiles

    def has_dynamic(self, entity):
        """ Check if a dynamic entity is in the block.

        Test:
        >>> b = Block()
        >>> b.has_dynamic('test')
        False
        >>> b._insert_dynamic('test')
        >>> b.has_dynamic('test')
        True
        """
        return entity in self._dynamics

    def has_static(self, entity):
        """ Check if a static entity is in the block.

        Test:
        >>> b = Block()
        >>> b.has_static('test')
        False
        >>> b._insert_static('test')
        >>> b.has_static('test')
        True
        """
        return entity in self._statics

    def has_tile(self, tile):
        """ Check if a tile is in the block.

        Test:
        >>> b = Block()
        >>> b.has_tile('test')
        False
        >>> b._insert_tile('test')
        >>> b.has_tile('test')
        True
        """
        return tile in self._tiles

    def _insert_dynamic(self, entity):
        """ Insert a dynamic entity.
        Don't use this, instead use region.set_pos().

        Test:
        >>> b = Block()
        >>> b.has_dynamic('test')
        False
        >>> b._insert_dynamic('test')
        >>> b.has_dynamic('test')
        True
        """
        self._dynamics.append(entity)

    def _insert_static(self, entity):
        """ Insert a static entity.
        Don't use this, instead use region.set_pos().

        Test:
        >>> b = Block()
        >>> b.has_static('test')
        False
        >>> b._insert_static('test')
        >>> b.has_static('test')
        True
        """
        self._blocked = {}
        self._statics.append(entity)

    def _insert_tile(self, tile):
        """ Insert a tile.
        Don't use this, instead use region.set_pos().

        Test:
        >>> b = Block()
        >>> b.has_tile('test')
        False
        >>> b._insert_tile('test')
        >>> b.has_tile('test')
        True
        """
        self._blocked = {}
        self._tiles.append(tile)

    def is_blocking(self, blocked):
        """ Checks if one of the entities would block.

        Test:
        >>> from data.world import tile
        >>> from data.world import dynamicentity
        >>> t = tile.Tile('tile')
        >>> t.blocking = ['block']
        >>> b = Block()
        >>> b._insert_tile(t)
        >>> b.is_blocking(['block'])
        True
        >>> b.is_blocking(['non-block'])
        False
        """
        # Statics may block more often so check first.
        key = tuple(blocked)
        if key not in self._blocked:
            result = self.__is_blocking_list(self._statics, blocked) or \
                     self.__is_blocking_list(self._tiles, blocked)
            self._blocked[key] = result
        return self._blocked[key]

    def remove_dynamic(self, entity):
        """ Removes a dynamic entity.

        Test:
        >>> b = Block()
        >>> b.has_dynamic('test')
        False
        >>> b._insert_dynamic('test')
        >>> b.has_dynamic('test')
        True
        >>> b.remove_dynamic('test')
        >>> b.has_dynamic('test')
        False
        """
        self._dynamics.remove(entity)

    def remove_static(self, entity):
        """ Removes a static entity.

        Test:
        >>> b = Block()
        >>> b.has_static('test')
        False
        >>> b._insert_static('test')
        >>> b.has_static('test')
        True
        >>> b.remove_static('test')
        >>> b.has_static('test')
        False
        """
        self._blocked = {}
        self._statics.remove(entity)

    def remove_tile(self, tile):
        """ Removes a tile.

        Test:
        >>> b = Block()
        >>> b.has_tile('test')
        False
        >>> b._insert_tile('test')
        >>> b.has_tile('test')
        True
        >>> b.remove_tile('test')
        >>> b.has_tile('test')
        False
        """
        self._blocked = {}
        self._tiles.remove(tile)

    def __is_blocking_list(self, entity_list, blocked):
        """ Execute blocking test on given list. """
        for entity in entity_list:
            if any(b in blocked for b in entity.blocking):
                return True
        return False

if __name__ == '__main__':
    print('Executing doctest.')
    import doctest
    doctest.testmod()