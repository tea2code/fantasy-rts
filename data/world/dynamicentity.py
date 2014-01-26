from data.world.entity import blocking, entity, movable


class DynamicEntity(entity.Entity, blocking.Blocked, movable.Walking):
    """ A dynamic entity. For example a horse.

    Member:
    _direction_suffix -- Mapping of direction to id suffix (dict).
    """

    def __init__(self, id):
        entity.Entity.__init__(self, id)
        blocking.Blocked.__init__(self)
        movable.Walking.__init__(self)
        self._direction_suffix = {
            movable.Direction.UP: '-up',
            movable.Direction.DOWN: '-down',
            movable.Direction.NORTH: '-north',
            movable.Direction.SOUTH: '-south',
            movable.Direction.WEST: '-west',
            movable.Direction.EAST: '-east'
        }

    def state_id(self):
        direction = self.direction if self.direction is not movable.Direction.STOP else self.last_direction
        id = self.id
        if direction in self._direction_suffix:
            id += self._direction_suffix[direction]
        else:
            # Use south as default suffix cause it will probably face the 4th wall.
            id += self._direction_suffix[movable.Direction.SOUTH]
        return id