from . import dynamicentity, point, staticentity, tile
from ..task import Factory as TaskFactory

class Factory:
    """ Factory class to create world entities. """

    @staticmethod
    def new_dynamic_entity(id, data, run_time):
        """ Creates and returns a new dynamic entity. """
        # Entity.
        config = data.config.entity.dynamics[id]
        entity = dynamicentity.DynamicEntity(id)
        entity.blocked = config.blocked
        entity.move_type = config.move_type

        # Initial task.
        TaskFactory.new_add_idle_task(entity, run_time, data)
        return entity

    @staticmethod
    def new_add_dynamic_entity(id, data, run_time, x=None, y=None, pos=None):
        """ Creates a new dynamic entity, adds it to the region at given
        position and returns it. """
        if pos is None:
            pos = point.Point(x, y)
        entity = Factory.new_dynamic_entity(id, data, run_time)
        data.game.region.set_pos(entity, pos)
        data.dirty_pos.add(pos)
        return entity

    @staticmethod
    def new_static_entity(id, data):
        """ Creates and returns a new static entity. """
        config = data.config.entity.statics[id]
        entity = staticentity.StaticEntity(id)
        entity.blocked = config.blocked
        entity.blocking = config.blocking
        return entity

    @staticmethod
    def new_add_static_entity(id, data, x=None, y=None, pos=None):
        """ Creates a new static entity, adds it to the region at given
        position and returns it. """
        if pos is None:
            pos = point.Point(x, y)
        entity = Factory.new_static_entity(id, data)
        data.game.region.set_pos(entity, pos)
        data.dirty_pos.add(pos)
        return entity

    @staticmethod
    def new_tile(id, data):
        """ Creates and returns a new tile. """
        config = data.config.entity.tiles[id]
        entity = tile.Tile(id)
        entity.blocking = config.blocking
        return entity

    @staticmethod
    def new_add_tile(id, data, x=None, y=None, pos=None):
        """ Creates a new tile, adds it to the region at given
        position and returns it. """
        if pos is None:
            pos = point.Point(x, y)
        entity = Factory.new_tile(id, data)
        data.game.region.set_pos(entity, pos)
        data.dirty_pos.add(pos)
        return entity

