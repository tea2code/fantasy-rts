from data.world.entity import blocking, entity


class Tile(entity.Entity, blocking.Blocking):
    """ A tile. """

    def __init__(self, id):
        entity.Entity.__init__(self, id)
        blocking.Blocking.__init__(self)