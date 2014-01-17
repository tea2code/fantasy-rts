from . import configuration
from . import game
from . import graphics

class Data:
    """ The main data object.

    Member:
    config -- The configuration state.
    dirty_pos -- List of positions which have changed in the last frame (list).
    fps -- List of frame per second for complete run time (list).
    game -- The game state.
    graphics -- The graphics state.
    """

    def __init__(self):
        self.config = configuration.Configuration()
        self.dirty_pos = set()
        self.fps = []
        self.game = game.Game()
        self.graphics = graphics.Graphics()