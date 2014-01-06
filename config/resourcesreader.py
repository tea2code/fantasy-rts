from . import basereader
from data.config import resource as resource_config
from data.config import resources
from data.config import resourcetype

class YamlResourcesReader(basereader.BaseYamlReader):
    """ Yaml reader for resource types.

    Constants:
    VALUE_NAME
    VALUE_NAMESPACE
    VALUE_RESOURCE
    VALUE_RESOURCES
    VALUE_TYPE
    VALUE_TYPES
    VALUE_TYPE_NAME
    VALUE_VALUE
    """

    VALUE_NAME = 'name'
    VALUE_NAMESPACE = 'namespace'
    VALUE_RESOURCE = 'resource'
    VALUE_RESOURCES = 'resources'
    VALUE_TYPE = 'type'
    VALUE_TYPES = 'types'
    VALUE_TYPE_NAME = 'type_name'
    VALUE_VALUE = 'value'

    def parse(self, root):
        """ Parse the style structure. Returns a graphics and a config
        style object. """

        namespace = self.read_req_string(root, self.VALUE_NAMESPACE)

        result = resources.Resources()
        if self.has(root, self.VALUE_RESOURCES):
            result.resources = self.__resources(namespace, root)
        if self.has(root, self.VALUE_TYPES):
            result.types = self.__types(namespace, root)
        return result

    def __resources(self, namespace, root):
        """ Parse resources. """
        resources = self.read_req_object(root, self.VALUE_RESOURCES)
        namespace_list = [namespace, self.read_req_string(resources, self.VALUE_NAMESPACE)]

        result = {}
        for resource in self.read_object(resources, self.VALUE_RESOURCE, []):
            name = self.read_req_string(resource, self.VALUE_NAME)
            id = self.namespace_to_id(namespace_list, name)
            type = self.read_req_string(resource, self.VALUE_TYPE)
            value = self.read_req_float(resource, self.VALUE_VALUE)
            result[id] = resource_config.Resource(value, type)
        return result

    def __types(self, namespace, root):
        """ Parse resource types. """
        types = self.read_req_object(root, self.VALUE_TYPES)
        namespace_list = [namespace, self.read_req_string(types, self.VALUE_NAMESPACE)]

        result = {}
        for type in self.read_object(types, self.VALUE_TYPE, []):
            name = self.read_req_string(type, self.VALUE_NAME)
            id = self.namespace_to_id(namespace_list, name)
            type_name = self.read_req_string(type, self.VALUE_TYPE_NAME)
            result[id] = resourcetype.ResourceType(type_name)
        return result