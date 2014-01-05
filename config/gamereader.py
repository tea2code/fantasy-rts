from . import basereader
from data import game

class YamlGameReader(basereader.BaseYamlReader):
    """ Yaml reader for game types.

    Constants:
    VALUE_NAME
    VALUE_NAMESPACE
    VALUE_SIZE_X
    VALUE_SIZE_Y
    """

    VALUE_NAME = 'name'
    VALUE_NAMESPACE = 'namespace'
    VALUE_SIZE_X = 'size_x'
    VALUE_SIZE_Y = 'size_y'

    def parse(self, root):
        """ Parse the game structure. Returns a game object. """

        result = game.Game()
        result.size_x = self.read_req_int(root, self.VALUE_SIZE_X)
        result.size_y = self.read_req_int(root, self.VALUE_SIZE_Y)
        return result