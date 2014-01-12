import random

from data import tasks
from data.world import creature, point, staticentity, tile


# TODO Refactor everything.

def new_creature(data, x, y, run_time):
    """ Adds a new creature at given position. Returns the creature. """
    # Create creature.
    c = creature.Creature('entity.dynamic.creature')
    c.blocked = data.config.entity.dynamics[c.id].blocked
    pos = point.Point(x, y)
    data.game.region.set_pos(c, pos)
    data.dirty_pos.add(pos)

    # Give creature first job -> Idle.
    due_time = run_time + random.random()
    new_task(data, c, tasks.TaskType.NEW_TASK_OR_IDLE, due_time)

    return c

def new_task(data, creature, type, time):
    """ Adds a new task for given creature. Returns the task. """
    task = tasks.Task(type, creature)
    data.game.tasks.insert(time, task)
    return task

def new_static_entity(data, id, x=None, y=None, pos=None):
    """ Add a new world entity object to given position. Returns the entity. """
    if pos is None:
        pos = point.Point(x, y)
    e = staticentity.StaticEntity(id)
    e.blocked = data.config.entity.statics[id].blocked
    e.blocking = data.config.entity.statics[id].blocking
    data.game.region.set_pos(e, pos)
    data.dirty_pos.add(pos)
    return e

def new_tile(data, id, x=None, y=None, pos=None):
    """ Add a new tile object to given position. Returns the tile. """
    if pos is None:
        pos = point.Point(x, y)
    t = tile.Tile(id)
    t.blocking = data.config.entity.tiles[id].blocking
    data.game.region.set_pos(t, pos)
    data.dirty_pos.add(pos)
    return t