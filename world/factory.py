import random

from data import tasks
from data.world import creature, point, worldentity


def new_creature(data, x, y, run_time):
    """ Adds a new creature at given position. Returns the creature. """
    # Create creature.
    c = creature.Creature()
    c.pos = point.Point(x, y)
    data.game.creatures.append(c)
    data.dirty_pos.add(c.pos)

    # Give creature first job -> Idle.
    due_time = run_time + random.random()
    new_task(data, c, tasks.TaskType.NEW_TASK_OR_IDLE, due_time)

    return c

def new_task(data, creature, type, time):
    """ Adds a new task for given creature. Returns the task. """
    task = tasks.Task(type, creature)
    data.game.tasks.insert(time, task)
    return task

def new_world_entity(data, id, x=None, y=None, pos=None):
    """ Add a new world entity object to given position. Returns the entity. """
    if pos is None:
        pos = point.Point(x, y)
    entity = worldentity.WorldEntity(id)
    entity.pos = pos
    data.game.world.append(entity)
    data.dirty_pos.add(entity.pos)
    return entity