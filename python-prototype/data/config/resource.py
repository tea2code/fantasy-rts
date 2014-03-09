class Resource:
    """ A config resource.

    Member:
    entity -- The id of the entity representing this resource (string).
    type -- The id of the resource type (string).
    """

    def __init__(self, type, entity):
        self.entity = entity
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