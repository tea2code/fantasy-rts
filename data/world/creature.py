from .. import direction
from data.world import point


class Creature:
    """ Basic creature.

    Member:
    direction -- The direction in which the creature is moving (data.direction).
    last_direction -- The previous direction in which the creature was moving (data.direction).
    pos -- The position of the creature (data.point).
    """

    def __init__(self):
        self.direction = direction.STOP
        self.last_direction = direction.DOWN
        self.pos = point.Point()

    def __str__(self):
        template = 'Creature({0})'
        return template.format(self.pos)