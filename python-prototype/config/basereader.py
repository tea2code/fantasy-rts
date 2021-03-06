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
        self.error_float = 'Value "{0}" must be floating point.'
        self.error_int = 'Value "{0}" must be integer.'
        self.error_missing = 'Missing value "{0}".'
        self.namespace_separator = '.'

    def is_type(self, root, name, type):
        """ Checks if the value is of given type.

        Test:
        >>> t = {'a':1, 'b':True, 'c':'c'}
        >>> b = BaseYamlReader()
        >>> b.is_type(t, 'a', bool)
        False
        >>> b.is_type(t, 'a', int)
        True
        >>> b.is_type(t, 'b', bool)
        True
        >>> b.is_type(t, 'c', str)
        True
        """
        return isinstance(root[name], type)

    def has(self, root, name):
        """ Checks if the given value exists.

        Test:
        >>> t = {'a':1, 'b':True, 'c':'c'}
        >>> b = BaseYamlReader()
        >>> b.has(t, 'a')
        True
        >>> b.has(t, 'd')
        False
        """
        return name in root

    def namespace_to_id(self, namespace, name):
        """ Creates an id from a namespace list and a name.

        Test:
        >>> b = BaseYamlReader()
        >>> ns = ['a', 'b']
        >>> n = 'c'
        >>> b.namespace_to_id(ns, n)
        'a.b.c'
        """
        namespace_path = self.namespace_separator.join(namespace)
        return '{0}{1}{2}'.format(namespace_path, self.namespace_separator, name)

    def read_boolean(self, root, name, default):
        """ Read a boolean value.

        >>> t = {'a':1, 'b':True, 'c':'c', 'd':0.1}
        >>> b = BaseYamlReader()
        >>> b.read_boolean(t, 'b', False)
        True
        >>> b.read_boolean(t, 'e', False)
        False
        """
        return self.__generic_read(root, name, default, bool, self.error_bool)

    def read_float(self, root, name, default):
        """ Read a floating point value.

        >>> t = {'a':1, 'b':True, 'c':'c', 'd':0.1}
        >>> b = BaseYamlReader()
        >>> b.read_float(t, 'd', 0.0)
        0.1
        >>> b.read_float(t, 'e', 0.0)
        0.0
        """
        return self.__generic_read(root, name, default, float, self.error_float)

    def read_int(self, root, name, default):
        """ Read an integer value.

        >>> t = {'a':1, 'b':True, 'c':'c', 'd':0.1}
        >>> b = BaseYamlReader()
        >>> b.read_int(t, 'a', 0)
        1
        >>> b.read_int(t, 'e', 0)
        0
        """
        return self.__generic_read(root, name, default, int, self.error_int)

    def read_object(self, root, name, default):
        """ Read an object value.

        >>> t = {'a':1, 'b':True, 'c':'c', 'd':0.1}
        >>> b = BaseYamlReader()
        >>> b.read_object(t, 'a', 0)
        1
        >>> b.read_object(t, 'e', 'Nope')
        'Nope'
        """
        if self.has(root, name):
            return root[name]
        else:
            return default

    def read_string(self, root, name, default):
        """ Read a string value.

        >>> t = {'a':1, 'b':True, 'c':'c', 'd':0.1}
        >>> b = BaseYamlReader()
        >>> b.read_string(t, 'c', '0')
        'c'
        >>> b.read_string(t, 'e', '0')
        '0'
        """
        return self.read_object(root, name, default)

    def read_req_boolean(self, root, name):
        """ Read a required boolean value.

        >>> t = {'a':1, 'b':True, 'c':'c', 'd':0.1}
        >>> b = BaseYamlReader()
        >>> b.read_req_boolean(t, 'b')
        True
        >>> b.read_req_boolean(t, 'c')
        Traceback (most recent call last):
        ...
        config.basereader.YamlError: Value "c" must be boolean.
        >>> b.read_req_boolean(t, 'e')
        Traceback (most recent call last):
        ...
        config.basereader.YamlError: Missing value "e".
        """
        return self.__generic_req_read(root, name, bool, self.error_bool)

    def read_req_float(self, root, name):
        """ Read a required floating point value.

        >>> t = {'a':1, 'b':True, 'c':'c', 'd':0.1}
        >>> b = BaseYamlReader()
        >>> b.read_req_float(t, 'd')
        0.1
        >>> b.read_req_float(t, 'c')
        Traceback (most recent call last):
        ...
        config.basereader.YamlError: Value "c" must be floating point.
        >>> b.read_req_float(t, 'e')
        Traceback (most recent call last):
        ...
        config.basereader.YamlError: Missing value "e".
        """
        return self.__generic_req_read(root, name, float, self.error_float)

    def read_req_int(self, root, name):
        """ Read an required integer value.

        >>> t = {'a':1, 'b':True, 'c':'c', 'd':0.1}
        >>> b = BaseYamlReader()
        >>> b.read_req_int(t, 'a')
        1
        >>> b.read_req_int(t, 'c')
        Traceback (most recent call last):
        ...
        config.basereader.YamlError: Value "c" must be integer.
        >>> b.read_req_int(t, 'e')
        Traceback (most recent call last):
        ...
        config.basereader.YamlError: Missing value "e".
        """
        return self.__generic_req_read(root, name, int, self.error_int)

    def read_req_object(self, root, name):
        """ Read a required object value.

        >>> t = {'a':1, 'b':True, 'c':'c', 'd':0.1}
        >>> b = BaseYamlReader()
        >>> b.read_req_object(t, 'c')
        'c'
        >>> b.read_req_object(t, 'e')
        Traceback (most recent call last):
        ...
        config.basereader.YamlError: Missing value "e".
        """
        if self.has(root, name):
            return root[name]
        else:
            raise YamlError(self.error_missing.format(name))

    def read_req_string(self, root, name):
        """ Read a required string value.

        >>> t = {'a':1, 'b':True, 'c':'c', 'd':0.1}
        >>> b = BaseYamlReader()
        >>> b.read_req_string(t, 'c')
        'c'
        >>> b.read_req_string(t, 'e')
        Traceback (most recent call last):
        ...
        config.basereader.YamlError: Missing value "e".
        """
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

if __name__ == '__main__':
    print('Executing doctest.')
    import doctest
    doctest.testmod()