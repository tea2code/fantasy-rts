from data.world.entity import blocking, entity


class Tile(entity.Entity, blocking.Blocking):
    """ A tile. """

    def __init__(self, id, config):
        entity.Entity.__init__(self, id, config)
        blocking.Blocking.__init__(self)