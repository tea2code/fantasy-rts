from . import basereader
from data.config import resource as resource_config

class YamlResourcesReader(basereader.BaseYamlReader):
    """ Yaml reader for resource types.

    Constants:
    NAME
    NAMESPACE
    RESOURCE
    RESOURCES
    TYPE
    TYPES
    VALUE
    """

    NAME = 'name'
    NAMESPACE = 'namespace'
    RESOURCE = 'resource'
    RESOURCES = 'resources'
    TYPE = 'type'
    TYPES = 'types'
    VALUE = 'value'

    def parse(self, root, data):
        """ Parse the style structure. Writes the parsed information into the
        data object. """
        namespace = self.read_req_string(root, self.NAMESPACE)

        if self.has(root, self.RESOURCES):
            self.__resources(namespace, root, data)
        if self.has(root, self.TYPES):
            self.__types(namespace, root, data)

    def __resources(self, namespace, root, data):
        """ Parse resources. """
        resources = self.read_req_object(root, self.RESOURCES)
        namespace_list = [namespace, self.read_req_string(resources, self.NAMESPACE)]

        for resource in self.read_object(resources, self.RESOURCE, []):
            name = self.read_req_string(resource, self.NAME)
            id = self.namespace_to_id(namespace_list, name)
            type = self.read_req_string(resource, self.TYPE)
            value = self.read_req_float(resource, self.VALUE)
            data.config.resources.resources[id] = resource_config.Resource(value, type)

    def __types(self, namespace, root, data):
        """ Parse resource types. """
        types = self.read_req_object(root, self.TYPES)
        namespace_list = [namespace, self.read_req_string(types, self.NAMESPACE)]

        for type in self.read_object(types, self.TYPE, []):
            name = self.read_req_string(type, self.NAME)
            id = self.namespace_to_id(namespace_list, name)
            data.config.resources.types[id] = resource_config.ResourceType()