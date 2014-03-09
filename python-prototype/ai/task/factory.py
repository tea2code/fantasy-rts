from .findresourcetask import FindResourceTaskParser
from .findentitytask import FindEntityTaskParser
from .gototask import GoToTaskParser
from .idletask import IdleTaskParser
from .randompointtask import RandomPointTaskParser
from .harvesttask import HarvestTaskParser
from .droptask import DropTaskParser
from .releaseresourcetask import ReleaseResourceTaskParser
from .pipelinevaluetask import PipelineValueTaskParser
from data import id as ID
from data.ai.task import BaseTaskParameter


class UnknownTaskException(Exception):
    """ Raised if a unknown task id is given. """


class Factory:
    """ Factory for task parsers.

    Member:
    _from_id -- Mapping of id to task for from_id(). Only for tasks without
                special parameter (dict).
    _from_task -- Mapping of id to task for from_task() (dict).
    """

    _from_id = {
        ID.AI_TASK_TYPE_DEMO_RANDOMPOINT: RandomPointTaskParser,
        ID.AI_TASK_TYPE_DROP: DropTaskParser,
        ID.AI_TASK_TYPE_FIND_ENTITY: FindEntityTaskParser,
        ID.AI_TASK_TYPE_GOTO: GoToTaskParser,
        ID.AI_TASK_TYPE_HARVEST: HarvestTaskParser,
        ID.AI_TASK_TYPE_RELEASE_RESOURCE: ReleaseResourceTaskParser
    }

    _from_task = {
        ID.AI_TASK_TYPE_DEMO_RANDOMPOINT: RandomPointTaskParser,
        ID.AI_TASK_TYPE_DROP: DropTaskParser,
        ID.AI_TASK_TYPE_FIND_ENTITY: FindEntityTaskParser,
        ID.AI_TASK_TYPE_FIND_RESOURCE: FindResourceTaskParser,
        ID.AI_TASK_TYPE_GOTO: GoToTaskParser,
        ID.AI_TASK_TYPE_HARVEST: HarvestTaskParser,
        ID.AI_TASK_TYPE_IDLE: IdleTaskParser,
        ID.AI_TASK_TYPE_PIPELINE_VALUE: PipelineValueTaskParser,
        ID.AI_TASK_TYPE_RELEASE_RESOURCE: ReleaseResourceTaskParser
    }

    @staticmethod
    def from_id(task_id, prev_task, data, pipeline=None, entity=None):
        """ Find the parser for the given task id and initialize. """
        config = data.config.ai.tasks[task_id]
        task_type = config.type

        base_task_parameter = BaseTaskParameter()
        base_task_parameter.type = task_type
        base_task_parameter.prev_task = prev_task
        base_task_parameter.entity = prev_task.entity if prev_task else entity
        base_task_parameter.input = config.input
        base_task_parameter.output = config.output
        base_task_parameter.pipeline = pipeline

        if task_type in Factory._from_id:
            parser = Factory._from_id[task_type](base_task_parameter=base_task_parameter,
                                                 variance_min=config.variance_min,
                                                 variance_max=config.variance_max)
        elif task_type == ID.AI_TASK_TYPE_FIND_RESOURCE:
            parser = FindResourceTaskParser(base_task_parameter=base_task_parameter,
                                            variance_min=config.variance_min,
                                            variance_max=config.variance_max,
                                            resource=config.resource)
        elif task_type == ID.AI_TASK_TYPE_IDLE:
            parser = IdleTaskParser(base_task_parameter=base_task_parameter,
                                    variance_min=config.variance_min,
                                    variance_max=config.variance_max,
                                    duration=config.duration)
        elif task_type == ID.AI_TASK_TYPE_PIPELINE_VALUE:
            parser = PipelineValueTaskParser(base_task_parameter=base_task_parameter,
                                             variance_min=config.variance_min,
                                             variance_max=config.variance_max,
                                             value=config.value)
        else:
            raise UnknownTaskException('Task type "{0}" is unknown.'.format(task_type))

        return parser

    @staticmethod
    def from_task(task):
        """ Finds the parser for the given task. """
        if task.type in Factory._from_task:
            parser = Factory._from_task[task.type](task=task)
        else:
            raise UnknownTaskException('Task id "{0}" is unknown.'.format(task.type))
        return parser