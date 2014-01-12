from . import entity

class DynamicEntity(entity.Entity):
    """ A dynamic entity. For example a horse."""

    def __init__(self, id):
        super().__init__(id)