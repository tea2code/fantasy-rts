from data.config import ID
from data.world.entity import blocking, entity, movable


class DynamicEntity(entity.Entity, blocking.Blocked, movable.Movable):
    """ A dynamic entity. For example a horse.

    Constants:
    DIRECTION_SUFFIX -- Mapping of direction to id suffix (dict).
    """

    DIRECTION_SUFFIX = {
        movable.Direction.UP: ID.STATE_DIRECTION_UP,
        movable.Direction.DOWN: ID.STATE_DIRECTION_DOWN,
        movable.Direction.NORTH: ID.STATE_DIRECTION_NORTH,
        movable.Direction.SOUTH: ID.STATE_DIRECTION_SOUTH,
        movable.Direction.WEST: ID.STATE_DIRECTION_WEST,
        movable.Direction.EAST: ID.STATE_DIRECTION_EAST
    }

    def __init__(self, id):
        entity.Entity.__init__(self, id)
        blocking.Blocked.__init__(self)
        movable.Movable.__init__(self)

    def state_id(self):
        id = self.id
        if self.direction in self.DIRECTION_SUFFIX:
            id += self.state_id_template.format(self.DIRECTION_SUFFIX[self.direction])
        else:
            # Use south as default suffix cause it will probably face the 4th wall.
            id += self.state_id_template.format(self.DIRECTION_SUFFIX[movable.Direction.SOUTH])
        return id