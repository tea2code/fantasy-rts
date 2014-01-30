class Entity:
    """ A world entity is a static element of the world. For example a simple
    tile of the ground, a dirt wall or a tree.

    Member:
    id -- The static entity id of the configuration (string).
    sprite_num -- The sprite number used (int).
    state_id_template -- The state id template (string).
    """

    def __init__(self, id, config):
        self.id = id
        self.sprite_num = None
        self.state_id_template = config.state_id

    def state_id(self):
        """ Returns the id adapted to the current internal state. """
        return self.id