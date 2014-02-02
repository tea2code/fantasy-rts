import random

from ai.task.factory import Factory as TaskFactory
from data.config import ID

class Director:
    """ The AI director manages all behaviour. """

    def tick(self, run_time, delta_time, data, tick):
        # Execute tasks.
        for task in data.game.tasks.take(run_time):
            task.execute_next(data)
            if not task.is_complete():
                self.__add_task(task, run_time, data)
            else:
                self.__new_task(task.entity, run_time, data)

    def __new_task(self, entity, run_time, data):
        """ Get the next task for the given entity. """
        if random.random() <= 0.9:
            task = TaskFactory.new_task(ID.TASK_IDLE, entity, data)
        else:
            task = TaskFactory.new_task(ID.TASK_GOTO, entity, data)
        self.__add_task(task, run_time, data)

    def __add_task(self, task, run_time, data):
        """ Add task to task list. """
        time = run_time + task.time()
        data.game.tasks.insert(time, task)