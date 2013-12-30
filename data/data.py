class Data:
    """ The main data object.

    Member:
    dirty_pos -- List of positions which have changed in the last frame (list).
    game -- The game state.
    graphics -- The graphics state.
    """

    def __init__(self):
        self.dirty_pos = set()
        self.game = None
        self.graphics = None