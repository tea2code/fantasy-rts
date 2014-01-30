from data.world.entity import blocking, entity


class StaticEntity(entity.Entity, blocking.Blocking, blocking.Blocked):
    """ A static entity. For example a tree."""

    def __init__(self, id, config):
        entity.Entity.__init__(self, id, config)
        blocking.Blocking.__init__(self)
        blocking.Blocked.__init__(self)