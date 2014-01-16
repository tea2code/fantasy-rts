import random

from . import basetask

class IdleTask(basetask.BaseTask):
    """ A task for entities which should idle. """

    def __init__(self, entity):
        super().__init__(entity)

    def time(self):
         min_time = 0.5
         return min_time + random.random()