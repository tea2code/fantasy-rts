class Graphics:
    """ The graphics state.

    Member:
    tile -- The size of a tile (int).
    view_x -- Size of the view port in x direction (int).
    view_y -- Size of the view port in y direction (int).
    view_offset_x -- Offset of the view port in x direction (int).
    view_offset_y -- Offset of the view port in y direction (int).
    view_updated -- Indicates if the view port position was updated (bool).
    window_title -- The window title template (string).
    """

    def __init__(self):
        self.tile = 16
        self.view_x = 40
        self.view_y = 30
        self.view_offset_x = 0
        self.view_offset_y = 0
        self.view_updated = False
        self.window_title = ''