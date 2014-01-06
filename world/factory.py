import random

from data import point
from data import tasks
from data import worldentity
from data.world import creature


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

def new_shrub(data, x, y):
    """ Add a new shrub object to given position. Returns the shrub. """
    s = worldentity.WorldEntity('entity.static.berry-shrub')
    s.pos = point.Point(x, y)
    data.game.world.append(s)
    data.dirty_pos.add(s.pos)

    return s

def new_task(data, creature, type, time):
    """ Adds a new task for given creature. Returns the task. """
    task = tasks.Task(type, creature)
    data.game.tasks.insert(time, task)
    return task