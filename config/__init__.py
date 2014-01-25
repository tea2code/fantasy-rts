import os
import yaml

from . import basereader, parser, validator as config_validator

def load_config(data, dir, load_file):
    """ Load the config dir. """
    # Read load file.
    reader = YamlLoadFileReader()
    yaml_files = reader.read(dir, load_file)

    # Parse files.
    yaml_parser = parser.YamlParser()
    yaml_parser.parse(data, yaml_files)

    # Validate configuration.
    validator = config_validator.Validator()
    validator.validate(data)

class YamlLoadFileReader(basereader.BaseYamlReader):
    """ Reads the load file in yaml format.

    Constants:
    VALUE_LOAD
    """

    VALUE_LOAD = 'load'

    def __init__(self, ):
        super().__init__()

    def read(self, dir, load_file):
        """ Reads the load file. """
        load_file = os.path.join(dir, load_file)
        with open(load_file, 'r') as file:
            root = yaml.safe_load(file)
        items = self.read_req_object(root, self.VALUE_LOAD)
        yaml_files = []
        for item in items:
            path = os.path.join(dir, item)
            if os.path.isdir(path):
                for file in os.listdir(path):
                    if file.endswith('.yaml') or file.endswith('.yml'):
                        yaml_files.append(os.path.join(path, file))
            else:
                yaml_files.append(path)
        return yaml_files