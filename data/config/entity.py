class Entity():
    """ A entity config.

    Member:
    statics -- Mapping of static id to static entity (dict).
    tiles -- Mapping of tile id to tile entity (dict).
    """

    def __init__(self):
        self.statics = {}
        self.tiles = {}