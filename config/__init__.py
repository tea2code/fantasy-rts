import os

from . import parser

def load_config(data, dir):
    """ Load the config dir. """
    yaml_files = []

    config_dirs = next(os.walk(dir))[1]
    for config_dir in config_dirs:
        config_dir = os.path.join(dir, config_dir)
        for file in os.listdir(config_dir):
            if file.endswith('.yaml') or file.endswith('.yml'):
                yaml_files.append(os.path.join(config_dir, file))

    yaml_parser = parser.YamlParser()
    yaml_parser.parse(data, yaml_files)