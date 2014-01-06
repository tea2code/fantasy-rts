class Resource():
    """ A config resource.

    Member:
    value -- The material value of the resource (float).
    type -- The id of the resource type (string).
    """

    def __init__(self, value, type):
        self.value = value
        self.type = type