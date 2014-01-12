from . import entity
from ..attributes import blocking, movable

class DynamicEntity(entity.Entity, blocking.Blocked, movable.Walking):
    """ A dynamic entity. For example a horse."""

    def __init__(self, id):
        entity.Entity.__init__(self, id)
        blocking.Blocked.__init__(self)
        movable.Walking.__init__(self)