from . import basetask
from data.ai.task import BaseTaskParameter, SuccessTask


class ReleaseResourceTaskParser(basetask.BaseTaskParser):
    """ Parses release resource tasks.

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
            data.game.region.release_resource(entity)
            self.successful = True
        else:
            raise basetask.PipelineParameterException()

        self.task = SuccessTask(self.base_task_parameter(), self.successful)
        return self.task

    def is_success(self):
        return self.successful