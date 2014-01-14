import random


class Director:
    """ The AI director manages all behaviour. """

    def tick(self, run_time, delta_time, data):
        # Execute tasks.
        for task in data.game.tasks.take(run_time):
            more_steps = task.execute_next(data)
            if more_steps:
                data.game.tasks.insert(task.time(), task)