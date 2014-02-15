class Attribute:
    """ An attribute config.

    Member:
    type -- The type id (string).
    """

    def __init__(self):
        self.type = ''


class Blocked(Attribute):
    """ Settings of a blocked attribute.

    Member:
    """

    def __init__(self):
        super().__init__()


class Blocking(Attribute):
    """ Settings of a blocking attribute.

    Member:
    """

    def __init__(self):
        super().__init__()


class DynamicEntity:
    """ A dynamic entity config.

    Member:
    blocked -- List of blocked attributes (list).
    moving -- List of moving attributes (list).
    """

    def __init__(self):
        self.blocked = []
        self.moving = []


class Entity:
    """ A entity config.

    Member:
    attributes -- List of known attributes (list).
    dynamics -- Mapping of dynamic id to dynamic entity (dict).
    statics -- Mapping of static id to static entity (dict).
    tiles -- Mapping of tile id to tile entity (dict).
    """

    def __init__(self):
        self.attributes = []
        self.dynamics = {}
        self.statics = {}
        self.tiles = {}


class Moving(Attribute):
    """ Settings of a moving attribute.

    Member:
    speed -- The moving speed (speed).
    """

    def __init__(self):
        super().__init__()
        self.speed = 0.0


class Resource(Attribute):
    """ Settings of a resource. """

    def __init__(self):
        super().__init__()


class StaticEntity:
    """ A static entity config.

    Member:
    blocked -- List of blocked attributes (list).
    blocking -- List of blocking attributes (list).
    resource -- List of resource attributes (list).
    """

    def __init__(self):
        self.blocked = []
        self.blocking = []
        self.resources = []


class TileEntity:
    """ A tile entity config.

    Member:
    blocking -- List of blocking attributes (list).
    """

    def __init__(self):
        self.blocking = []