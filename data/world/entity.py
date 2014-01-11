from . import point

class Entity:
    """ A world entity is a static element of the world. For example a simple
    tile of the ground, a dirt wall or a tree.

    Member:
    id -- The static entity id of the configuration (string).
    pos -- The position (data.point).
    """

    def __init__(self, id):
        self.id = id
        self.pos = point.Point()