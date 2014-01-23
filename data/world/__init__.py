from . import dynamicentity, staticentity, tile
from .point import Factory as PointFactory
from ..task import Factory as TaskFactory

class Factory:
    """ Factory class to create world entities.

    Constants:
    CACHE_STATICS  -- Indicates if static entities should be cached (bool).
    CACHE_TILES -- Indicates if tiles should be cached (bool).

    Member:
    _statics -- Maps already created static entities (dict).
    _tiles -- Maps already created tiles (dict).
    """

    CACHE_STATICS = False # TODO Currently not working. Entities disappear.
    CACHE_TILES = True
    _statics = {}
    _tiles = {}

    @staticmethod
    def new_dynamic_entity(id, data, run_time, init_task=True):
        """ Creates and returns a new dynamic entity. """
        # Entity.
        config = data.config.entity.dynamics[id]
        entity = dynamicentity.DynamicEntity(id)
        entity.blocked = [b.type for b in config.blocked]
        entity.moving = config.moving

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
        if Factory.CACHE_STATICS:
            if id not in Factory._statics:
                Factory._statics[id] = Factory.__new_static_entity(id, data)
            return Factory._statics[id]
        else:
            return Factory.__new_static_entity(id, data)

    @staticmethod
    def __new_static_entity(id, data):
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
        if Factory.CACHE_TILES:
            if id not in Factory._tiles:
                Factory._tiles[id] = Factory.__new_tile(id, data)
            return Factory._tiles[id]
        else:
            return Factory.__new_tile(id, data)

    @staticmethod
    def __new_tile(id, data):
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