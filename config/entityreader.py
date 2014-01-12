from . import basereader
from data.config import attribute as attributeentity
from data.config import dynamicentity
from data.config import entity
from data.config import staticentity
from data.config import tileentity

class YamlEntityReader(basereader.BaseYamlReader):
    """ Yaml reader for entity types.

    Constants:
    VALUE_ATTRIBUTE
    VALUE_ATTRIBUTE_CATEGORY
    VALUE_ATTRIBUTES
    VALUE_BLOCKED
    VALUE_BLOCKING
    VALUE_DYNAMIC
    VALUE_DYNAMICS
    VALUE_NAME
    VALUE_NAMESPACE
    VALUE_RESOURCE
    VALUE_RESOURCE_CHANCE
    VALUE_STATIC
    VALUE_STATICS
    VALUE_TILE
    VALUE_TILES
    """

    VALUE_ATTRIBUTE = 'attribute'
    VALUE_ATTRIBUTE_CATEGORY = 'attribute-category'
    VALUE_ATTRIBUTES = 'attributes'
    VALUE_BLOCKED = 'blocked'
    VALUE_BLOCKING = 'blocking'
    VALUE_DYNAMIC = 'dynamic'
    VALUE_DYNAMICS = 'dynamics'
    VALUE_NAME = 'name'
    VALUE_NAMESPACE = 'namespace'
    VALUE_RESOURCE = 'resource'
    VALUE_RESOURCE_CHANCE = 'resource_chance'
    VALUE_STATIC = 'static'
    VALUE_STATICS = 'statics'
    VALUE_TILE = 'tile'
    VALUE_TILES = 'tiles'

    def parse(self, root):
        """ Parse the style structure. Returns a graphics and a config
        style object. """

        namespace = self.read_req_string(root, self.VALUE_NAMESPACE)

        result = entity.Entity()
        if self.has(root, self.VALUE_ATTRIBUTES):
            result.attributes = self.__attributes(namespace, root)
        if self.has(root, self.VALUE_DYNAMICS):
            result.dynamics = self.__dynamics(namespace, root)
        if self.has(root, self.VALUE_STATICS):
            result.statics = self.__statics(namespace, root)
        if self.has(root, self.VALUE_TILES):
            result.tiles = self.__tiles(namespace, root)
        return result

    def __attributes(self, namespace, root):
        """ Parse attributes. """
        attributes = self.read_req_object(root, self.VALUE_ATTRIBUTES)
        namespace_attr = self.read_req_string(attributes, self.VALUE_NAMESPACE)

        result = {}
        for category in self.read_object(attributes, self.VALUE_ATTRIBUTE_CATEGORY, []):
            namespace_list = [namespace, namespace_attr, self.read_req_string(category, self.VALUE_NAMESPACE)]
            for attribute in self.read_object(category, self.VALUE_ATTRIBUTE, []):
                name = self.read_req_string(attribute, self.VALUE_NAME)
                id = self.namespace_to_id(namespace_list, name)
                result[id] = attributeentity.Attribute()
        return result

    def __dynamics(self, namespace, root):
        """ Parse dynamics. """
        dynamics = self.read_req_object(root, self.VALUE_DYNAMICS)
        namespace_list = [namespace, self.read_req_string(dynamics, self.VALUE_NAMESPACE)]

        result = {}
        for dynamic in self.read_object(dynamics, self.VALUE_DYNAMIC, []):
            name = self.read_req_string(dynamic, self.VALUE_NAME)
            id = self.namespace_to_id(namespace_list, name)
            d = dynamicentity.DynamicEntity()
            d.blocked = self.read_object(dynamic, self.VALUE_BLOCKED, [])
            result[id] = d
        return result

    def __statics(self, namespace, root):
        """ Parse statics. """
        statics = self.read_req_object(root, self.VALUE_STATICS)
        namespace_list = [namespace, self.read_req_string(statics, self.VALUE_NAMESPACE)]

        result = {}
        for static in self.read_object(statics, self.VALUE_STATIC, []):
            name = self.read_req_string(static, self.VALUE_NAME)
            id = self.namespace_to_id(namespace_list, name)
            resource = self.read_string(static, self.VALUE_RESOURCE, None)
            chance = self.read_float(static, self.VALUE_RESOURCE_CHANCE, 0.0)
            s = staticentity.StaticEntity(resource, chance)
            s.blocked = self.read_object(static, self.VALUE_BLOCKED, [])
            s.blocking = self.read_object(static, self.VALUE_BLOCKING, [])
            result[id] = s
        return result

    def __tiles(self, namespace, root):
        """ Parse tiles. """
        tiles = self.read_req_object(root, self.VALUE_TILES)
        namespace_list = [namespace, self.read_req_string(tiles, self.VALUE_NAMESPACE)]

        result = {}
        for tile in self.read_object(tiles, self.VALUE_TILE, []):
            name = self.read_req_string(tile, self.VALUE_NAME)
            id = self.namespace_to_id(namespace_list, name)
            t = tileentity.TileEntity()
            t.blocking = self.read_object(tile, self.VALUE_BLOCKING, [])
            result[id] = t
        return result