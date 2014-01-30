from . import basereader
from data import configuration
from data import graphics

class YamlConfigReader(basereader.BaseYamlReader):
    """ Yaml reader for config types.

    Constants:
    FPS
    MAX_FRAME_TIME
    NUM_FPS_AVG
    SCROLL_WIDTH_X
    SCROLL_WIDTH_Y
    STATE_ID
    VIEW_X
    VIEW_Y
    WINDOW_TITLE
    """

    FPS = 'fps'
    MAX_FRAME_TIME = 'max_frame_time'
    NUM_FPS_AVG = 'num_fps_avg'
    SCROLL_WIDTH_X = 'scroll_width_x'
    SCROLL_WIDTH_Y = 'scroll_width_y'
    STATE_ID = 'state_id'
    VIEW_X = 'view_x'
    VIEW_Y = 'view_y'
    WINDOW_TITLE = 'window_title'

    def parse(self, root, data):
        """ Parse the game structure. Writes the parsed information into the
        data object. """
        data.config.fps = self.read_int(root, self.FPS, data.config.fps)
        data.config.max_frame_time = self.read_float(root, self.MAX_FRAME_TIME, data.config.max_frame_time)
        data.config.num_fps_avg = self.read_int(root, self.NUM_FPS_AVG, data.config.num_fps_avg)
        data.config.scroll_width_x = self.read_int(root, self.SCROLL_WIDTH_X, data.config.scroll_width_x)
        data.config.scroll_width_y = self.read_int(root, self.SCROLL_WIDTH_Y, data.config.scroll_width_y)
        data.config.state_id = self.read_string(root, self.STATE_ID, data.config.state_id)

        data.graphics.view_x = self.read_int(root, self.VIEW_X, data.graphics.view_x)
        data.graphics.view_y = self.read_int(root, self.VIEW_Y, data.graphics.view_y)
        data.graphics.window_title = self.read_string(root, self.WINDOW_TITLE, data.graphics.window_title)