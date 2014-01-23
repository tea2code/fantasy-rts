from . import basereader
from data import game

class YamlGameReader(basereader.BaseYamlReader):
    """ Yaml reader for game types.

    Constants:
    SIZE_X
    SIZE_Y
    """

    SIZE_X = 'size_x'
    SIZE_Y = 'size_y'

    def parse(self, root, data):
        """ Parse the game structure. Writes the parsed information into the
        data object. """
        data.game.size_x = self.read_req_int(root, self.SIZE_X)
        data.game.size_y = self.read_req_int(root, self.SIZE_Y)