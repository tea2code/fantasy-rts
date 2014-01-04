class Data:
    """ The main data object.

    Member:
    config -- The configuration state.
    dirty_pos -- List of positions which have changed in the last frame (list).
    game -- The game state.
    graphics -- The graphics state.
    """

    def __init__(self):
        self.config = None
        self.dirty_pos = set()
        self.game = None
        self.graphics = None