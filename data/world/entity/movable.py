from data.world.point import Factory as PointFactory

class Direction:
    """ Direction constants. """

    STOP = PointFactory.new_point(0, 0, 0)
    NORTH = PointFactory.new_point(0, -1, 0)
    SOUTH = PointFactory.new_point(0, 1, 0)
    EAST = PointFactory.new_point(1, 0, 0)
    WEST = PointFactory.new_point(-1, 0, 0)
    UP = PointFactory.new_point(0, 0, 1)
    DOWN = PointFactory.new_point(0, 0, -1)

class Movable:
    """ Defines the walking attribute.

    Member:
    direction -- The direction in which the creature is moving (direction).
    moving -- Maps id to speed (dict).
    """

    def __init__(self):
        self.direction = Direction.STOP
        self.moving = {}