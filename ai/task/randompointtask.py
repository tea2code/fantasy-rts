import random

from . import basetask
from data.ai.task import BaseTaskParameter, BaseTask


class RandomPointTaskParser(basetask.BaseTaskParser):
    """ Parses random point tasks."""

    def __init__(self, base_task_parameter=None, variance_min=None,
                 variance_max=None, task=None):
        super().__init__(base_task_parameter, variance_min, variance_max, task)

    def create_new(self, data):
        if self.output:
            goal = data.game.region.free_random_pos(self.entity.blocked, 0)
            self.pipeline[self.output] = goal

        base_task_parameter = BaseTaskParameter()
        base_task_parameter.type = self.type
        base_task_parameter.prev_task = self.prev_task
        base_task_parameter.entity = self.entity
        base_task_parameter.input = self.input
        base_task_parameter.output = self.output
        base_task_parameter.pipeline = self.pipeline
        self.task = BaseTask(base_task_parameter)
        return self.task

    def execute_next(self, data):
        pass

    def is_complete(self):
        return True

    def is_success(self):
        return True

    def time(self):
        return 0.0