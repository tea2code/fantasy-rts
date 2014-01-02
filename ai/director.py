import random

from data import tasks


class Director:
    """ The AI director manages all behaviour. """

    def tick(self, run_time, delta_time, data):
        # Check tasks.
        for task in data.game.tasks.take(run_time):
            if task.type == tasks.TaskType.NEW_TASK_OR_IDLE:
                time = run_time + random.random()
                data.game.tasks.insert(time, task)
