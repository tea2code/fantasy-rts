from .gototask import GoToTaskParser
from .idletask import IdleTaskParser
from .randompointtask import RandomPointTaskParser
from data import id as ID
from data.ai.task import BaseTaskParameter


class UnknownTaskException(Exception):
    """ Raised if a unknown task id is given. """


class Factory:
    """ Factory for task parsers. """

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
        if task_type == ID.AI_TASK_TYPE_GOTO:
            parser = GoToTaskParser(base_task_parameter=base_task_parameter,
                                    variance_min=config.variance_min,
                                    variance_max=config.variance_max)
        elif task_type == ID.AI_TASK_TYPE_IDLE:
            parser = IdleTaskParser(base_task_parameter=base_task_parameter,
                                    variance_min=config.variance_min,
                                    variance_max=config.variance_max,
                                    duration=config.duration)
        elif task_type == ID.AI_TASK_TYPE_DEMO_RANDOMPOINT:
            parser = RandomPointTaskParser(base_task_parameter=base_task_parameter,
                                           variance_min=config.variance_min,
                                           variance_max=config.variance_max)
        else:
            raise UnknownTaskException('Task type "{0}" is unknown.'.format(task_type))
        return parser

    @staticmethod
    def from_task(task):
        """ Finds the parser for the given task. """
        if task.type == ID.AI_TASK_TYPE_GOTO:
            parser = GoToTaskParser(task=task)
        elif task.type == ID.AI_TASK_TYPE_IDLE:
            parser = IdleTaskParser(task=task)
        elif task.type == ID.AI_TASK_TYPE_DEMO_RANDOMPOINT:
            parser = RandomPointTaskParser(task=task)
        else:
            raise UnknownTaskException('Task id "{0}" is unknown.'.format(task.type))
        return parser