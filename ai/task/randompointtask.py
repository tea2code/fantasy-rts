import random

from . import basetask
from data.ai.task import BaseTask


class RandomPointTaskParser(basetask.BaseTaskParser):
    """ Parses random point tasks."""

    def __init__(self, base_task_parameter=None, variance_min=None,
                 variance_max=None, task=None):
        super().__init__(base_task_parameter, variance_min, variance_max, task)

    def create_new(self, data):
        if self.output:
            goal = data.game.region.free_random_pos(self.entity.blocked, 0)
            self.pipeline[self.output] = goal
        else:
            raise basetask.PipelineParameterException()

        self.task = BaseTask(self.base_task_parameter())
        return self.task

    def is_success(self):
        return True