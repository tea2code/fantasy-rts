from . import entity
from ..attributes import blocking

class Tile(entity.Entity, blocking.Blocking):
    """ A tile. """

    def __init__(self, id):
        entity.Entity.__init__(self, id)
        blocking.Blocking.__init__(self)