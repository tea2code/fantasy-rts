from .config import ai
from .config import entity
from .config import resource
from .config import style

class Configuration:
    """ The configuration data object.

    Member:
    ai -- The ai config (data.config.ai).
    config_dir -- The config directory (string).
    entity -- The entity config (data.config.entity).
    fps -- The should be frame rate (int).
    keys -- Mapping of action ID to key (dict).
    max_frame_time -- Maximum time a frame may take (float).
    num_fps_avg -- Number of frames to keep for calculation fps (int).
    resources -- The resources config (data.config.resources).
    scroll_width_x -- Number of tiles scrolling changes the view port in x direction (int).
    scroll_width_y -- Number of tiles scrolling changes the view port in y direction (int).
    state_id -- The template for the state id (int).
    style -- The style config (data.config.style).
    """

    def __init__(self):
        self.ai = ai.Ai()
        self.config_dir = ''
        self.entity = entity.Entity()
        self.fps = 100
        self.keys = {}
        self.max_frame_time = 0.25
        self.num_fps_avg = 1000
        self.resources = resource.Resources()
        self.scroll_width_x = 3
        self.scroll_width_y = 3
        self.state_id = '{0}'
        self.style = style.Style()