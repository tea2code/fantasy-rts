import random

from . import idletask

class Factory:
    """ Factory class to create tasks. """
    # TODO Move time span to config.

    @staticmethod
    def new_idle_task(entity):
        """ Creates a new idle task for given entity. Returns the task. """
        task = idletask.IdleTask(entity)
        return task

    @staticmethod
    def new_add_idle_task(entity, run_time, data):
        """ Creates a new idle task and adds it to the task list. Returns the
        task. """
        min_time = 0.5
        t = run_time + min_time + Factory.__time_variance(0, 1)
        task = Factory.new_idle_task(entity)
        data.game.tasks.insert(t, task)
        return task

    @staticmethod
    def __time_variance(min, max):
        """ Calculates a time variance for tasks. """
        return random.uniform(min, max)