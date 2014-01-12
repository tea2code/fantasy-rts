from .. import direction

class Walking:
    """ Defines the walking attribute.

    Member:
    direction -- The direction in which the creature is moving (data.direction).
    last_direction -- The previous direction in which the creature was moving (data.direction).
    speed -- The speed in positions per second (float).
    """

    def __init__(self):
        self.direction = direction.STOP
        self.last_direction = direction.DOWN
        self.speed = 0.0