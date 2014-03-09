from . import basetask
from data.ai.task import SuccessTask


class DropTaskParser(basetask.BaseTaskParser):
    """ Parses drop tasks.

    Member:
    successful -- Indicates if task is successful (bool).
    """

    def __init__(self, base_task_parameter=None, variance_min=None,
                 variance_max=None, task=None):
        super().__init__(base_task_parameter, variance_min, variance_max, task)
        self.successful = task.successful if task else False

    def create_new(self, data):
        if self.input in self.pipeline:
            self.successful = True
            pos = data.game.region.get_pos(self.entity)
            entity = self.pipeline[self.input]
            data.game.region.set_pos(entity, pos)
        else:
            raise basetask.PipelineParameterException()

        self.task = SuccessTask(self.base_task_parameter(), self.successful)
        return self.task

    def is_success(self):
        return self.successful