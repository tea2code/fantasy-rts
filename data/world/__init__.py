from . import dynamicentity, staticentity, tile
from .point import Factory as PointFactory
from ai.task import Factory as TaskFactory

class Factory:
    """ Factory class to create world entities."""

    @staticmethod
    def new_dynamic_entity(id, data, run_time, init_task=True):
        """ Creates and returns a new dynamic entity. """
        # Entity.
        config = data.config.entity.dynamics[id]
        entity = dynamicentity.DynamicEntity(id)
        entity.blocked = [b.type for b in config.blocked]
        entity.move_type = config.moving[0].type
        entity.speed = config.moving[0].speed

        # Initial task.
        if init_task:
            TaskFactory.new_add_idle_task(entity, run_time, data)

        return entity

    @staticmethod
    def new_add_dynamic_entity(id, data, run_time, x=None, y=None, z=None, pos=None, init_task=True):
        """ Creates a new dynamic entity, adds it to the region at given
        position and returns it. """
        if pos is None:
            pos = PointFactory.new_point(x, y, z)
        entity = Factory.new_dynamic_entity(id, data, run_time, init_task)
        data.game.region.set_pos(entity, pos)
        data.dirty_pos.add(pos)
        return entity

    @staticmethod
    def new_static_entity(id, data):
        """ Creates and returns a new static entity. """
        config = data.config.entity.statics[id]
        entity = staticentity.StaticEntity(id)
        entity.blocked = [b.type for b in config.blocked]
        entity.blocking = [b.type for b in config.blocking]
        return entity

    @staticmethod
    def new_add_static_entity(id, data, x=None, y=None, z=None, pos=None):
        """ Creates a new static entity, adds it to the region at given
        position and returns it. """
        if pos is None:
            pos = PointFactory.new_point(x, y, z)
        entity = Factory.new_static_entity(id, data)
        data.game.region.set_pos(entity, pos)
        data.dirty_pos.add(pos)
        return entity

    @staticmethod
    def new_tile(id, data):
        """ Creates and returns a new tile. """
        config = data.config.entity.tiles[id]
        entity = tile.Tile(id)
        entity.blocking = [b.type for b in config.blocking]
        return entity

    @staticmethod
    def new_add_tile(id, data, x=None, y=None, z=None, pos=None):
        """ Creates a new tile, adds it to the region at given
        position and returns it. """
        if pos is None:
            pos = PointFactory.new_point(x, y, z)
        entity = Factory.new_tile(id, data)
        data.game.region.set_pos(entity, pos)
        data.dirty_pos.add(pos)
        return entity