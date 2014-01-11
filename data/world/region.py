class UnknownEntityException(Exception):
    """ Thrown if a entity is not known. """

    def __init__(self, entity):
        message = 'There is no position stored for entity "{0}".'.format(entity)
        Exception.__init__(self, message)

class Region:
    """ Represents a region in the world. A region is a map the player is
    currently on. The map consists of a 3 dimensional cube split into positions
    representing a single block.

    Member:
    _entity_pos -- Maps entities to their exact positions (dict).
    _pos_block -- Maps positions to the block on this position (dict).
    """

    def __init__(self):
        self._entity_pos = {}
        self._pos_block = {}

    def get_block(self, pos):
        """ Returns the block at the given position.

        Test:
        >>> from . import entity
        >>> e = entity.Entity('id')
        >>> from . import point
        >>> p = point.Point()
        >>> r = Region()
        >>> 'Todo'
        """
        return self._pos_block[pos]

    def get_pos(self, entity):
        """ Returns the exact position of the given entity. Throws
        UnknownEntityException for unknown entities.

        Test:
        >>> from . import entity
        >>> e = entity.Entity('id')
        >>> from . import point
        >>> p = point.Point()
        >>> r = Region()
        >>> r.get_pos(e) # doctest: +ELLIPSIS
        Traceback (most recent call last):
        ...
        data.world.region.UnknownEntityException: ...
        >>> r.set_pos(e, p)
        >>> r.get_pos(e) is p
        True
        """
        if not entity in self._entity_pos:
            raise UnknownEntityException(entity)
        return self._entity_pos[entity]

    def remove_entity(self, entity):
        """ Removes an entity.

        Test:
        >>> from . import entity
        >>> e = entity.Entity('id')
        >>> from . import point
        >>> p = point.Point()
        >>> r = Region()
        >>> r.set_pos(e, p)
        >>> r.get_pos(e) is p
        True
        >>> r.remove_entity(e)
        >>> r.get_pos(e) # doctest: +ELLIPSIS
        Traceback (most recent call last):
        ...
        data.world.region.UnknownEntityException: ...
        """
        del self._entity_pos[entity]

    def set_pos(self, entity, pos):
        """ Sets the entity to the given position.

        Test: See get_pos().
        """
        self._entity_pos[entity] = pos

if __name__ == '__main__':
    print('Executing doctest.')
    import doctest
    doctest.testmod()