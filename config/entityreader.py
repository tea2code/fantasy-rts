from . import basereader
from data.config import entity
from data.config import staticentity

class YamlEntityReader(basereader.BaseYamlReader):
    """ Yaml reader for entity types.

    Constants:
    VALUE_NAME
    VALUE_NAMESPACE
    VALUE_STATIC
    VALUE_STATICS
    VALUE_RESOURCE
    VALUE_RESOURCE_CHANCE
    """

    VALUE_NAME = 'name'
    VALUE_NAMESPACE = 'namespace'
    VALUE_STATIC = 'static'
    VALUE_STATICS = 'statics'
    VALUE_RESOURCE = 'resource'
    VALUE_RESOURCE_CHANCE = 'resource_chance'

    def parse(self, root):
        """ Parse the style structure. Returns a graphics and a config
        style object. """

        namespace = self.read_req_string(root, self.VALUE_NAMESPACE)

        result = entity.Entity()
        if self.has(root, self.VALUE_STATICS):
            result.statics = self.__statics(namespace, root)
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
            result[id] = staticentity.StaticEntity(resource, chance)
        return result