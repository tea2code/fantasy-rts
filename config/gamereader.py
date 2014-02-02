from . import basereader

class YamlGameReader(basereader.BaseYamlReader):
    """ Yaml reader for game types.

    Constants:
    FOOD_PLANT
    MAPPINGS
    RACE_PLAYER
    SIZE_X
    SIZE_Y
    TILE_GROUND
    TILE_WALL
    WOOD_PLANT
    """

    FOOD_PLANT = 'food_plant'
    MAPPINGS = 'mappings'
    RACE_PLAYER = 'race_player'
    SIZE_X = 'size_x'
    SIZE_Y = 'size_y'
    TILE_GROUND = 'tile_ground'
    TILE_WALL = 'tile_wall'
    WOOD_PLANT = 'wood_plant'

    def parse(self, root, data):
        """ Parse the game structure. Writes the parsed information into the
        data object. """
        data.game.size_x = self.read_int(root, self.SIZE_X, data.game.size_x)
        data.game.size_y = self.read_int(root, self.SIZE_Y, data.game.size_y)

        if self.has(root, self.MAPPINGS):
            self.__mappings(root, data)

    def __mappings(self, root, data):
        """ Mapping config. """
        mappings = self.read_req_object(root, self.MAPPINGS)

        data.game.race_player = self.read_string(mappings, self.RACE_PLAYER, data.game.race_player)
        data.game.food_plant = self.read_string(mappings, self.FOOD_PLANT, data.game.race_player)
        data.game.wood_plant = self.read_string(mappings, self.WOOD_PLANT, data.game.race_player)
        data.game.tile_ground = self.read_string(mappings, self.TILE_GROUND, data.game.race_player)
        data.game.tile_wall = self.read_string(mappings, self.TILE_WALL, data.game.race_player)