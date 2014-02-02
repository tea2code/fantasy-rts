from . import basereader
from data.config import key as key_class

class YamlConfigReader(basereader.BaseYamlReader):
    """ Yaml reader for config types.

    Constants:
    ACTION
    FPS
    KEY
    KEYS
    MAX_FRAME_TIME
    NUM_FPS_AVG
    SCROLL_WIDTH_X
    SCROLL_WIDTH_Y
    STATE_ID
    VIEW_X
    VIEW_Y
    WINDOW_TITLE
    """

    ACTION = 'action'
    FPS = 'fps'
    KEY = 'key'
    KEYS = 'keys'
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

        if self.has(root, self.KEYS):
            self.__keys(root, data)

    def __keys(self, root, data):
        """ Parse keys. """
        for key_config in self.read_req_object(root, self.KEYS):
            action = self.read_req_string(key_config, self.ACTION)
            key = self.read_req_string(key_config, self.KEY).upper()
            data.config.keys[action] = key_class.Key(key)