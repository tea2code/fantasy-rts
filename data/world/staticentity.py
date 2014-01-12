from . import entity
from ..attributes import blocking

class StaticEntity(entity.Entity, blocking.Blocking, blocking.Blocked):
    """ A static entity. For example a tree."""

    def __init__(self, id):
        entity.Entity.__init__(self, id)
        blocking.Blocking.__init__(self)
        blocking.Blocked.__init__(self)