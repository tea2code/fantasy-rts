import random

from . import basetask
from data.ai.task import IdleTask


class IdleTaskParser(basetask.BaseTaskParser):
    """ Parses idle tasks.

    Member:
    duration -- The idle duration (float).
    """

    def __init__(self, type=None, variance_min=None, variance_max=None,
                 prev_task=None, entity=None, task=None, duration=None):
        super().__init__(type, variance_min, variance_max, prev_task, entity, task)
        self.duration = task.duration if task else duration

    def cleanup(self, data):
        pass

    def create_new(self, data):
        if isinstance(self.duration, list):
            if self.prev_task and self.prev_task.type == self.type:
                durations = self.duration
                self.duration = durations[-1]
                for index, duration in enumerate(durations[:-1]):
                    if duration + self.variance_min <= self.prev_task.duration <= duration + self.variance_max:
                        self.duration = durations[index + 1]
            else:
                self.duration = self.duration[0]
        self.duration = self.duration + random.uniform(self.variance_min, self.variance_max)
        self.task = IdleTask(self.type, self.prev_task, self.entity, self.duration)
        return self.task

    def execute_next(self, data):
        pass

    def is_complete(self):
        return True

    def is_success(self):
        return True

    def time(self):
        return self.duration