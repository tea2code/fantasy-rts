from . import basetask
from data.ai.task import SuccessTask


class PipelineValueTaskParser(basetask.BaseTaskParser):
    """ Parses pipeline value tasks.

    Member:
    value -- The value to set).
    successful -- Indicates if task is successful (bool).
    """

    def __init__(self, base_task_parameter=None, variance_min=None,
                 variance_max=None, task=None, value=None):
        super().__init__(base_task_parameter, variance_min, variance_max, task)
        self.value = value
        if self.input in self.pipeline:
            self.value = self.pipeline[self.input]
        self.successful = task.successful if task else False

    def create_new(self, data):
        if self.output:
            self.pipeline[self.output] = self.value
        else:
            raise basetask.PipelineParameterException()
        self.successful = True
        self.task = SuccessTask(self.base_task_parameter(), self.successful)
        return self.task

    def is_success(self):
        return self.successful