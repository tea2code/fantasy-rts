import random
import world.factory

from . import basetask
from data.ai.task import SuccessTask


class HarvestTaskParser(basetask.BaseTaskParser):
    """ Parses harvest tasks.

    Member:
    successful -- Indicates if task is successful (bool).
    """

    def __init__(self, base_task_parameter=None, variance_min=None,
                 variance_max=None, task=None):
        super().__init__(base_task_parameter, variance_min, variance_max, task)
        self.successful = task.successful if task else False

    def create_new(self, data):
        if self.input in self.pipeline and self.output:
            entity = self.pipeline[self.input]
            pos = data.game.region.get_pos(entity)
            data.dirty_pos.add(pos)
            data.game.region.remove_entity(entity)
            resource = data.config.entity.statics[entity.id].resources[0]
            if random.random() <= resource.chance:
                self.successful = True
                id = data.config.resources.resources[resource.type].entity
                resource_entity = world.factory.new_static_entity(id, data)
                if self.output:
                    self.pipeline[self.output] = resource_entity
        else:
            raise basetask.PipelineParameterException()

        self.task = SuccessTask(self.base_task_parameter(), self.successful)
        return self.task

    def is_success(self):
        return self.successful