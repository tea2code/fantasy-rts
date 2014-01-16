
from . import gototask, idletask

class Factory:
    """ Factory class to create tasks. """
    # TODO Move time span to config.

    @staticmethod
    def new_goto_task(entity, goal, data):
        """ Creates a new goto task for given entity. Returns the task. """
        task = gototask.GoToTask(entity, goal, data)
        return task

    @staticmethod
    def new_add_goto_task(entity, run_time, goal, data):
        """ Creates a new goto task and adds it to the task list. Returns the
        task. """
        task = Factory.new_goto_task(entity, goal, data)
        t = run_time + task.time()
        data.game.tasks.insert(t, task)
        return task

    @staticmethod
    def new_idle_task(entity):
        """ Creates a new idle task for given entity. Returns the task. """
        task = idletask.IdleTask(entity)
        return task

    @staticmethod
    def new_add_idle_task(entity, run_time, data):
        """ Creates a new idle task and adds it to the task list. Returns the
        task. """
        task = Factory.new_idle_task(entity)
        t = run_time + task.time()
        data.game.tasks.insert(t, task)
        return task