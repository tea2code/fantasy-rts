from . import basereader
from data import configuration
from data import graphics

class YamlConfigReader(basereader.BaseYamlReader):
    """ Yaml reader for config types.

    Constants:
    FPS
    MAX_FRAME_TIME
    SCROLL_WIDTH_X
    SCROLL_WIDTH_Y
    VIEW_X
    VIEW_Y
    WINDOW_TITLE
    """

    FPS = 'fps'
    MAX_FRAME_TIME = 'max_frame_time'
    SCROLL_WIDTH_X = 'scroll_width_x'
    SCROLL_WIDTH_Y = 'scroll_width_y'
    VIEW_X = 'view_x'
    VIEW_Y = 'view_y'
    WINDOW_TITLE = 'window_title'

    def parse(self, root, data):
        """ Parse the game structure. Writes the parsed information into the
        data object. """
        data.config.fps = self.read_req_int(root, self.FPS)
        data.config.max_frame_time = self.read_req_float(root, self.MAX_FRAME_TIME)
        data.config.scroll_width_x = self.read_req_int(root, self.SCROLL_WIDTH_X)
        data.config.scroll_width_y = self.read_req_int(root, self.SCROLL_WIDTH_Y)

        data.graphics.view_x = self.read_req_int(root, self.VIEW_X)
        data.graphics.view_y = self.read_req_int(root, self.VIEW_Y)
        data.graphics.window_title = self.read_req_string(root, self.WINDOW_TITLE)