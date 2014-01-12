class StaticEntity():
    """ A static entity config.

    Member:
    blocked -- List of blocked ids (list).
    blocking -- List of blocking ids (list).
    resource -- The resource id or None (string).
    resource_chance -- The chance that a resource is dropped (float).
    """

    def __init__(self, resource, resource_chance):
        self.blocked = []
        self.blocking = []
        self.resource = resource
        self.resource_chance = resource_chance