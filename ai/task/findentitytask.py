from . import basetask
from data.ai.task import SuccessTask


class FindEntityTaskParser(basetask.BaseTaskParser):
    """ Parses find entity tasks.

    Member:
    successful -- Indicates if task is successful (bool).
    """

    def __init__(self, base_task_parameter=None, variance_min=None,
                 variance_max=None, task=None):
        super().__init__(base_task_parameter, variance_min, variance_max, task)
        self.successful = task.successful if task else False

    def create_new(self, data):
        if self.input in self.pipeline:
            entity = self.pipeline[self.input]
            pos = data.game.region.get_pos(entity)
            if pos:
                self.successful = True
                self.pipeline[self.output] = pos
        else:
            raise basetask.PipelineParameterException()
        
        self.task = SuccessTask(self.base_task_parameter(), self.successful)
        return self.task

    def is_success(self):
        return self.successful