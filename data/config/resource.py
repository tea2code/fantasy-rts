class Resource:
    """ A config resource.

    Member:
    value -- The material value of the resource (float).
    type -- The id of the resource type (string).
    """

    def __init__(self, value, type):
        self.value = value
        self.type = type

class Resources:
    """ Config resources.

    Member:
    resources -- Resource id to resource mapping (dict).
    types -- Type id to type mapping (dict).
    """

    def __init__(self):
        self.resources = {}
        self.types = {}

class ResourceType:
    """ A config resource type.

    Member:
    """

    def __init__(self):
        pass