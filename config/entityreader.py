from . import basereader
from data.config import entity

class YamlEntityReader(basereader.BaseYamlReader):
    """ Yaml reader for entity types.

    Constants:
    ATTRIBUTE
    ATTRIBUTES
    CATEGORY
    BLOCKED
    BLOCKING
    DYNAMIC
    DYNAMICS
    MOVING
    NAME
    NAMESPACE
    RESOURCE
    SPEED
    STATIC
    STATICS
    TILE
    TILES
    TYPE
    """

    ATTRIBUTE = 'attribute'
    ATTRIBUTES = 'attributes'
    BLOCKED = 'blocked'
    BLOCKING = 'blocking'
    CATEGORY = 'category'
    DYNAMIC = 'dynamic'
    DYNAMICS = 'dynamics'
    MOVING = 'moving'
    NAME = 'name'
    NAMESPACE = 'namespace'
    RESOURCE = 'resource'
    SPEED = 'speed'
    STATIC = 'static'
    STATICS = 'statics'
    TILE = 'tile'
    TILES = 'tiles'
    TYPE = 'type'

    def parse(self, root, data):
        """ Parse the style structure. Writes the parsed information into the
        data object. """
        namespace = self.read_req_string(root, self.NAMESPACE)

        if self.has(root, self.ATTRIBUTES):
            self.__attributes(namespace, root, data)
        if self.has(root, self.DYNAMICS):
            self.__dynamics(namespace, root, data)
        if self.has(root, self.STATICS):
            self.__statics(namespace, root, data)
        if self.has(root, self.TILES):
            self.__tiles(namespace, root, data)

    def __attributes(self, namespace, root, data):
        """ Parse attributes. """
        attributes = self.read_req_object(root, self.ATTRIBUTES)
        namespace_attr = self.read_req_string(attributes, self.NAMESPACE)

        for category in self.read_object(attributes, self.CATEGORY, []):
            namespace_list = [namespace, namespace_attr, self.read_req_string(category, self.NAMESPACE)]
            for attribute in self.read_object(category, self.ATTRIBUTE, []):
                name = self.read_req_string(attribute, self.NAME)
                id = self.namespace_to_id(namespace_list, name)
                data.config.entity.attributes.append(id)

    def __blocked(self, root):
        """ Reads the blocked attributes of a entity. """
        blockeds = self.read_req_object(root, self.BLOCKED)
        blockeds = blockeds if blockeds else []
        result = []
        for blocked in blockeds:
            blocked_obj = entity.Blocked()
            blocked_obj.type = self.read_req_string(blocked, self.TYPE)
            result.append(blocked_obj)
        return result

    def __blocking(self, root):
        """ Reads the blocking attributes of a entity. """
        blockings = self.read_req_object(root, self.BLOCKING)
        blockings = blockings if blockings else []
        result = []
        for blocking in blockings:
            blocking_obj = entity.Blocking()
            blocking_obj.type = self.read_req_string(blocking, self.TYPE)
            result.append(blocking_obj)
        return result

    def __dynamics(self, namespace, root, data):
        """ Parse dynamics. """
        dynamics = self.read_req_object(root, self.DYNAMICS)
        namespace_list = [namespace, self.read_req_string(dynamics, self.NAMESPACE)]

        for dynamic in self.read_object(dynamics, self.DYNAMIC, []):
            name = self.read_req_string(dynamic, self.NAME)
            id = self.namespace_to_id(namespace_list, name)
            d = entity.DynamicEntity()
            d.blocked = self.__blocked(dynamic)
            d.moving = self.__moving(dynamic)
            data.config.entity.dynamics[id] = d

    def __moving(self, root):
        """ Reads the moving attributes of a entity. """
        movings = self.read_req_object(root, self.MOVING)
        movings = movings if movings else []
        result = []
        for moving in movings:
            moving_obj = entity.Moving()
            moving_obj.type = self.read_req_string(moving, self.TYPE)
            moving_obj.speed = self.read_req_float(moving, self.SPEED)
            result.append(moving_obj)
        return result

    def __resource(self, root):
        """ Reads the resource attributes of a entity. """
        resources = self.read_req_object(root, self.RESOURCE)
        resources = resources if resources else []
        result = []
        for resource in resources:
            resource_obj = entity.Resource()
            resource_obj.type = self.read_req_string(resource, self.TYPE)
            result.append(resource_obj)
        return result

    def __statics(self, namespace, root, data):
        """ Parse statics. """
        statics = self.read_req_object(root, self.STATICS)
        namespace_list = [namespace, self.read_req_string(statics, self.NAMESPACE)]

        for static in self.read_object(statics, self.STATIC, []):
            name = self.read_req_string(static, self.NAME)
            id = self.namespace_to_id(namespace_list, name)
            s = entity.StaticEntity()
            s.blocked = self.__blocked(static)
            s.blocking = self.__blocking(static)
            s.resources = self.__resource(static)
            data.config.entity.statics[id] = s

    def __tiles(self, namespace, root, data):
        """ Parse tiles. """
        tiles = self.read_req_object(root, self.TILES)
        namespace_list = [namespace, self.read_req_string(tiles, self.NAMESPACE)]

        for tile in self.read_object(tiles, self.TILE, []):
            name = self.read_req_string(tile, self.NAME)
            id = self.namespace_to_id(namespace_list, name)
            t = entity.TileEntity()
            t.blocking = self.__blocking(tile)
            data.config.entity.tiles[id] = t