from . import entity

class StaticEntity(entity.Entity):
    """ A static entity. For example a tree."""

    def __init__(self, id):
        super().__init__(id)