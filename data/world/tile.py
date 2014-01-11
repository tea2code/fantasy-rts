from . import entity

class Tile(entity.Entity):
    """ A tile. """

    def __init__(self, id):
        super().__init__(id)