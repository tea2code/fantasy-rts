import os
import yaml

from . import basereader, parser

def load_config(data, dir, load_file):
    """ Load the config dir. """
    reader = YamlLoadFileReader(dir, load_file)
    yaml_files = reader.read()
    yaml_parser = parser.YamlParser()
    yaml_parser.parse(data, yaml_files)

class YamlLoadFileReader(basereader.BaseYamlReader):
    """ Reads the load file in yaml format.

    Constants:
    VALUE_LOAD

    Member:
    dir -- The config directory (string).
    load_file -- The load order file (string).
    """

    VALUE_LOAD = 'load'

    def __init__(self, dir, load_file):
        super().__init__()
        self.dir = dir
        self.load_file = load_file

    def read(self):
        """ Reads the load file. """
        load_file = os.path.join(self.dir, self.load_file)
        with open(load_file, 'r') as file:
            root = yaml.safe_load(file)
        items = self.read_req_object(root, self.VALUE_LOAD)
        yaml_files = []
        for item in items:
            path = os.path.join(self.dir, item)
            if os.path.isdir(path):
                for file in os.listdir(path):
                    if file.endswith('.yaml') or file.endswith('.yml'):
                        yaml_files.append(os.path.join(path, file))
            else:
                yaml_files.append(path)
        return yaml_files