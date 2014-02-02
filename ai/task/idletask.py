import random

from ai.task import basetask
from data.config import ID

class IdleTask(basetask.BaseTask):
    """ A task for entities which should idle.

    Member:
    _complete -- Indicates if the task is complete (bool).
    _time -- Time to idle (float).
    """

    def __init__(self, entity, config, variance_min, variance_max):
        super().__init__(entity, variance_min, variance_max)
        self._complete = False
        variance = random.uniform(variance_min, variance_max)
        self._time = config.parameters[ID.TASK_PARAMETER_TIME] + variance

    def execute_next(self, data):
        self._complete = True

    def is_complete(self):
        return self._complete

    def time(self):
         return self._time