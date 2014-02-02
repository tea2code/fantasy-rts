import yaml

from . import aireader
from . import configreader
from . import entityreader
from . import gamereader
from . import resourcesreader
from . import stylereader

class UnknownReaderException(Exception):
    """" Thrown if a unknown key for a reader is found. """

class YamlParser:
    """ Parses configuration files in yaml format.

    Constants:
    AI
    CONFIG
    ENTITY
    GAME
    RESOURCES
    STYLE

    Member:
    _readers -- Mapping of key to reader (dict).
    """

    AI = 'ai'
    CONFIG = 'config'
    ENTITY = 'entity'
    GAME = 'game'
    RESOURCES = 'resources'
    STYLE = 'style'

    def __init__(self):
        self._readers = {
            self.AI: aireader.YamlAiReader(),
            self.CONFIG: configreader.YamlConfigReader(),
            self.ENTITY: entityreader.YamlEntityReader(),
            self.GAME: gamereader.YamlGameReader(),
            self.RESOURCES: resourcesreader.YamlResourcesReader(),
            self.STYLE: stylereader.YamlStyleReader()
        }

    def parse(self, data, files):
        """ Parse the given list of yaml files and updates the data object. """
        for file_path in files:
            with open(file_path, 'r') as file:
                root = yaml.safe_load(file)
            for key in root:
                parser = self.__parser(key)
                parser.parse(root[key], data)

    def __parser(self, key):
        """ Creates the reader for given key. """
        parser = None
        if key in self._readers:
            parser = self._readers[key]
        else:
            msg = 'No reader found for key "{0}".'.format(key)
            raise UnknownReaderException(msg)
        return parser