class Game:
    """ The game state.

    Member:
    tile -- The size of a tile (int).
    tile_x -- The size of the map in x direction (int).
    tile_y -- The size of the map in y direction (int).
    """

    def __init__(self):
        self.tile = 16
        self.tile_x = 100
        self.tile_y = 100