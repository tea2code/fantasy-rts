from . import basetask
from data.ai.task import BaseTaskParameter, SuccessTask


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