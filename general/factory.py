import random

from data import creature
from data import point
from data import tasks

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