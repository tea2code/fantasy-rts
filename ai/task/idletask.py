import random

from . import basetask
from data.ai.task import BaseTaskParameter, IdleTask


class IdleTaskParser(basetask.BaseTaskParser):
    """ Parses idle tasks.

    Member:
    duration -- The idle duration (float).
    """

    def __init__(self, base_task_parameter=None, variance_min=None,
                 variance_max=None, task=None, duration=None):
        super().__init__(base_task_parameter, variance_min, variance_max, task)
        self.duration = duration
        if task:
            self.duration = self.task.duration
        elif self.input in self.pipeline:
            self.duration = self.pipeline[self.input]

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

        base_task_parameter = BaseTaskParameter()
        base_task_parameter.type = self.type
        base_task_parameter.prev_task = self.prev_task
        base_task_parameter.entity = self.entity
        base_task_parameter.input = self.input
        base_task_parameter.output = self.output
        base_task_parameter.pipeline = self.pipeline
        self.task = IdleTask(base_task_parameter, self.duration)
        return self.task

    def execute_next(self, data):
        pass

    def is_complete(self):
        return True

    def is_success(self):
        return True

    def time(self):
        return self.duration