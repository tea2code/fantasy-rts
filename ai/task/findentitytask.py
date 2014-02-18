from . import basetask
from data.ai.task import BaseTaskParameter, SuccessTask


class FindEntityTaskParser(basetask.BaseTaskParser):
    """ Parses find entity tasks.

    Member:
    successful -- Indicates if task is successful (bool).
    """

    def __init__(self, base_task_parameter=None, variance_min=None,
                 variance_max=None, task=None):
        super().__init__(base_task_parameter, variance_min, variance_max, task)
        self.successful = task.successful if task else False

    def cleanup(self, data):
        pass

    def create_new(self, data):
        if self.input in self.pipeline:
            entity = self.pipeline[self.input]
            pos = data.game.region.get_pos(entity)
            if pos:
                self.successful = True
                self.pipeline[self.output] = pos
        
        base_task_parameter = BaseTaskParameter()
        base_task_parameter.type = self.type
        base_task_parameter.prev_task = self.prev_task
        base_task_parameter.entity = self.entity
        base_task_parameter.input = self.input
        base_task_parameter.output = self.output
        base_task_parameter.pipeline = self.pipeline
        self.task = SuccessTask(base_task_parameter, self.successful)
        return self.task

    def execute_next(self, data):
        pass

    def is_complete(self):
        return True

    def is_success(self):
        return self.successful

    def time(self):
        return 0.0