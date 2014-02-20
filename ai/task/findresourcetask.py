from . import basetask
from data.ai.task import SuccessTask


class FindResourceTaskParser(basetask.BaseTaskParser):
    """ Parses find resource tasks.

    Member:
    resource -- The resource type to find (string).
    successful -- Indicates if task is successful (bool).
    """

    def __init__(self, base_task_parameter=None, variance_min=None,
                 variance_max=None, task=None, resource=None):
        super().__init__(base_task_parameter, variance_min, variance_max, task)
        self.resource = resource
        if self.input in self.pipeline:
            self.resource = self.pipeline[self.input]
        self.successful = task.successful if task else False

    def create_new(self, data):
        entity_pos = data.game.region.get_pos(self.entity)
        resource_entity = data.game.region.find_resource(self.resource, entity_pos)
        if resource_entity:
            self.successful = True
            if self.output:
                self.pipeline[self.output] = resource_entity
            else:
                raise basetask.PipelineParameterException()
        
        self.task = SuccessTask(self.base_task_parameter(), self.successful)
        return self.task

    def is_success(self):
        return self.successful