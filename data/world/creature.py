from data.world import dynamicentity


class Creature(dynamicentity.DynamicEntity):
    """ Basic creature."""

    def __init__(self, id):
        dynamicentity.DynamicEntity.__init__(self, id)