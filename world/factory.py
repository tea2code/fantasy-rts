from ai.task import factory as task_parser
from data.world import dynamicentity, staticentity, tile
from data.world.point import Factory as PointFactory


def new_dynamic_entity(id, data, run_time, init_task=True):
    """ Creates and returns a new dynamic entity. """
    # Entity.
    config = data.config.entity.dynamics[id]
    entity = dynamicentity.DynamicEntity(id)
    __init_entity(entity, data.config)
    entity.blocked = [b.type for b in config.blocked]
    for moving in config.moving:
        entity.moving[moving.type] = moving.speed

    # Initial task.
    if init_task:
        task_id = 'ai.task.idle'
        parser = task_parser.Factory.from_id(task_id, None, data, entity=entity)
        task = parser.create_new(data)
        data.game.tasks.insert(run_time + parser.time(), task)

    return entity


def new_add_dynamic_entity(id, data, run_time, x=None, y=None, z=None, pos=None, init_task=True):
    """ Creates a new dynamic entity, adds it to the region at given
    position and returns it. """
    if pos is None:
        pos = PointFactory.new_point(x, y, z)
    entity = new_dynamic_entity(id, data, run_time, init_task)
    data.game.region.set_pos(entity, pos)
    data.dirty_pos.add(pos)
    return entity


def new_static_entity(id, data):
    """ Creates and returns a new static entity. """
    config = data.config.entity.statics[id]
    entity = staticentity.StaticEntity(id)
    __init_entity(entity, data.config)
    entity.blocked = [b.type for b in config.blocked]
    entity.blocking = [b.type for b in config.blocking]
    return entity


def new_add_static_entity(id, data, x=None, y=None, z=None, pos=None):
    """ Creates a new static entity, adds it to the region at given
    position and returns it. """
    if pos is None:
        pos = PointFactory.new_point(x, y, z)
    entity = new_static_entity(id, data)
    data.game.region.set_pos(entity, pos)
    data.dirty_pos.add(pos)
    return entity


def new_tile(id, data):
    """ Creates and returns a new tile. """
    config = data.config.entity.tiles[id]
    entity = tile.Tile(id)
    __init_entity(entity, data.config)
    entity.blocking = [b.type for b in config.blocking]
    return entity


def new_add_tile(id, data, x=None, y=None, z=None, pos=None):
    """ Creates a new tile, adds it to the region at given
    position and returns it. """
    if pos is None:
        pos = PointFactory.new_point(x, y, z)
    entity = new_tile(id, data)
    data.game.region.set_pos(entity, pos)
    data.dirty_pos.add(pos)
    return entity


def __init_entity(entity, config):
    """ Initialize entity with common configuration. """
    entity.state_id_template = config.state_id