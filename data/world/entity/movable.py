class Direction:
    """ Direction constants. """

    STOP = 0
    NORTH = 1
    SOUTH = 2
    EAST = 3
    WEST = 4
    UP = 5
    DOWN = 6

class Walking:
    """ Defines the walking attribute.

    Member:
    direction -- The direction in which the creature is moving (direction).
    last_direction -- The previous direction in which the creature was moving (direction).
    move_type -- Type of moving (string).
    speed -- The speed in positions per second (float).
    """

    def __init__(self):
        self.direction = Direction.STOP
        self.last_direction = Direction.SOUTH
        self.move_type = ''
        self.speed = 0.0