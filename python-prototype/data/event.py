class BaseEvent:
    """ Base class for events.

    Member:
    type -- The event type (string).
    """

    def __init__(self, type):
        self.type = type


class PosEvent(BaseEvent):
    """ A positional event.

    Member:
    action -- The action to execute on this position (string).
    pos -- The position (data.world.point).
    """

    def __init__(self, type, pos, action=None):
        super().__init__(type)
        self.action = action
        self.pos = pos