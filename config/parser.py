import yaml

from . import configreader
from . import gamereader
from . import stylereader

class YamlParser:
    """ Parses configuration files in yaml format.

    Constants:
    NAME_CONFIG
    NAME_GAME
    NAME_STYLE
    """

    NAME_CONFIG = 'config'
    NAME_GAME = 'game'
    NAME_STYLE = 'style'

    def parse(self, data, files):
        """ Parse the given list of yaml files and updates the data object. """
        for file_path in files:
            with open(file_path, 'r') as file:
                root = yaml.safe_load(file)
            for key in root:
                if key == self.NAME_STYLE:
                    # Parse.
                    parser = stylereader.YamlStyleReader()
                    value_graphics, value_style = parser.parse(root[key])

                    # Update.
                    data.graphics.tile_x = value_graphic.tile_x
                    data.graphics.tile_y = value_graphic.tile_y

                    if value_style.default_mapping:
                        data.config.style.default_mapping = value_style.default_mapping
                    data.config.style.images.update(value_style.images)
                    data.config.style.mappings.update(value_style.mappings)
                    data.config.style.sprites.update(value_style.sprites)

                elif key == self.NAME_GAME:
                    # Parse.
                    parser = gamereader.YamlGameReader()
                    value = parser.parse(root[key])

                    # Update.
                    data.game.size_x = value.size_x
                    data.game.size_y = value.size_y

                elif key == self.NAME_CONFIG:
                    # Parse.
                    parser = configreader.YamlConfigReader()
                    value_config, value_graphic = parser.parse(root[key])

                    # Update.
                    data.config.fps = value_config.fps
                    data.config.max_frame_time = value_config.max_frame_time
                    data.config.scroll_width_x = value_config.scroll_width_x
                    data.config.scroll_width_y = value_config.scroll_width_y

                    data.graphics.view_x = value_graphic.view_x
                    data.graphics.view_y = value_graphic.view_y
                    data.graphics.window_title = value_graphic.window_title