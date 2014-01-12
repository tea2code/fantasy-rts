class Entity():
    """ A entity config.

    Member:
    attributes -- Mapping of attribute id to attribute entity (dict).
    dynamics -- Mapping of dynamic id to dynamic entity (dict).
    statics -- Mapping of static id to static entity (dict).
    tiles -- Mapping of tile id to tile entity (dict).
    """

    def __init__(self):
        self.attributes = {}
        self.dynamics = {}
        self.statics = {}
        self.tiles = {}