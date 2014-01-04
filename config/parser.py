import yaml

from . import stylereader

class YamlParser:
    """ Parses configuration files in yaml format.

    Constants:
    NAME_STYLE
    """

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
                    value = parser.parse(root[key])

                    # Update.
                    if value.default_mapping:
                        data.config.style.default_mapping = value.default_mapping
                    data.config.style.images.update(value.images)
                    data.config.style.mappings.update(value.mappings)
                    data.config.style.sprites.update(value.sprites)