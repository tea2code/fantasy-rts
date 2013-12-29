from . import level

class Game:
    """ The game state.

    Member:
    level -- The game level (data.level).
    tile_x -- The size of the map in x direction (int).
    tile_y -- The size of the map in y direction (int).
    """

    def __init__(self):
        self.level = level.Level()
        self.tile_x = 100
        self.tile_y = 100