class YamlError(Exception):
    """ Exception thrown by yaml reader. """

class BaseYamlReader:
    """ Base reader for yaml files.

    Member:
    error_bool -- Boolean type error (string).
    error_int -- Integer type error (string).
    error_missing -- Error in case of missing value (string).
    namespace_separator -- The namespace separator (string).
    """

    def __init__(self):
        self.error_bool = 'Value "{0}" must be boolean.'
        self.error_int = 'Value "{0}" must be integer.'
        self.error_missing = 'Missing value "{0}".'
        self.namespace_separator = '.'

    def is_type(self, root, name, type):
        """ Checks if the value is of given type. """
        return isinstance(root[name], type)

    def has(self, root, name):
        """ Checks if the given value exists. """
        return name in root

    def namespace_to_id(self, namespace, name):
        """ Creates an id from a namespace list and a name. """
        namespace_path = self.namespace_separator.join(namespace)
        return '{0}{1}{2}'.format(namespace_path, self.namespace_separator, name)

    def read_boolean(self, root, name, default):
        """ Read a boolean value. """
        return self.__generic_read(root, name, default, bool, self.error_bool)

    def read_int(self, root, name, default):
        """ Read an integer value. """
        return self.__generic_read(root, name, default, int, self.error_int)

    def read_object(self, root, name, default):
        """ Read an object value. """
        if self.has(root, name):
            return root[name]
        else:
            return default

    def read_string(self, root, name, default):
        """ Read a string value. """
        return self.read_object(root, name, default)

    def read_req_boolean(self, root, name):
        """ Read a required boolean value. """
        return self.__generic_req_read(root, name, bool, self.error_bool)

    def read_req_int(self, root, name):
        """ Read an required integer value. """
        return self.__generic_req_read(root, name, int, self.error_int)

    def read_req_object(self, root, name):
        """ Read a required object value. """
        if self.has(root, name):
            return root[name]
        else:
            raise YamlError(self.error_missing.format(name))

    def read_req_string(self, root, name):
        """ Read a required string value. """
        return self.read_req_object(root, name)

    def __generic_read(self, root, name, default, type, error_type):
        """ Generic read function for non-required values. """
        if self.has(root, name):
            if self.is_type(root, name, type):
                return root[name]
            else:
                raise YamlError(error_type.format(name))
        else:
            return default

    def __generic_req_read(self, root, name, type, error_type):
        """ Generic read function for required values. """
        if self.has(root, name):
            if self.is_type(root, name, type):
                return root[name]
            else:
                raise YamlError(error_type.format(name))
        else:
            raise YamlError(self.error_missing.format(name))