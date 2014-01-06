from .config import entity
from .config import resources
from .config import style

class Configuration:
    """ The configuration data object.

    Member:
    config_dir -- The config directory (string).
    entity -- The entity config (data.config.entity).
    fps -- The should be frame rate (int).
    max_frame_time -- Maximum time a frame may take (float).
    resources -- The resources config (data.config.resources).
    scroll_width_x -- Number of tiles scrolling changes the view port in x direction (int).
    scroll_width_y -- Number of tiles scrolling changes the view port in y direction (int).
    style -- The style config (data.config.style).
    """

    def __init__(self):
        self.config_dir = ''
        self.entity = entity.Entity()
        self.fps = 100
        self.max_frame_time = 0.25
        self.resources = resources.Resources()
        self.scroll_width_x = 3
        self.scroll_width_y = 3
        self.style = style.Style()