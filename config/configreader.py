from . import basereader
from data import configuration
from data import graphics

class YamlConfigReader(basereader.BaseYamlReader):
    """ Yaml reader for config types.

    Constants:
    VALUE_FPS
    VALUE_MAX_FRAME_TIME
    VALUE_NAME
    VALUE_NAMESPACE
    VALUE_SCROLL_WIDTH_X
    VALUE_SCROLL_WIDTH_Y
    VALUE_VIEW_X
    VALUE_VIEW_Y
    VALUE_WINDOW_TITLE
    """

    VALUE_FPS = 'fps'
    VALUE_MAX_FRAME_TIME = 'max_frame_time'
    VALUE_NAME = 'name'
    VALUE_NAMESPACE = 'namespace'
    VALUE_SCROLL_WIDTH_X = 'scroll_width_x'
    VALUE_SCROLL_WIDTH_Y = 'scroll_width_y'
    VALUE_VIEW_X = 'view_x'
    VALUE_VIEW_Y = 'view_y'
    VALUE_WINDOW_TITLE = 'window_title'

    def parse(self, root):
        """ Parse the game structure. Returns a configuration and a
        graphics object. """

        result_config = configuration.Configuration()
        result_config.fps = self.read_req_int(root, self.VALUE_FPS)
        result_config.max_frame_time = self.read_req_float(root, self.VALUE_MAX_FRAME_TIME)
        result_config.scroll_width_x = self.read_req_int(root, self.VALUE_SCROLL_WIDTH_X)
        result_config.scroll_width_y = self.read_req_int(root, self.VALUE_SCROLL_WIDTH_Y)

        result_graphic = graphics.Graphics()
        result_graphic.view_x = self.read_req_int(root, self.VALUE_VIEW_X)
        result_graphic.view_y = self.read_req_int(root, self.VALUE_VIEW_Y)
        result_graphic.window_title = self.read_req_string(root, self.VALUE_WINDOW_TITLE)

        return result_config, result_graphic