from . import entity
from ..attributes import blocking

class DynamicEntity(entity.Entity, blocking.Blocked):
    """ A dynamic entity. For example a horse."""

    def __init__(self, id):
        entity.Entity.__init__(self, id)
        blocking.Blocked.__init__(self)