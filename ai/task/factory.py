from .gototask import GoToTaskParser
from .idletask import IdleTaskParser
from data import id as ID


class UnknownTaskException(Exception):
    """ Raised if a unknown task id is given. """


class Factory:
    """ Factory for task parsers. """

    @staticmethod
    def from_id(task_id, prev_task, data, entity=None):
        """ Find the parser for the given task id and initialize. """
        config = data.config.ai.tasks[task_id]
        task_type = config.type
        entity = prev_task.entity if prev_task else entity
        if task_type == ID.AI_TASK_TYPE_GOTO:
            goal = data.game.region.free_random_pos(prev_task.entity.blocked, 0)
            parser = GoToTaskParser(type=task_type,
                                    variance_min=config.variance_min,
                                    variance_max=config.variance_max,
                                    prev_task=prev_task,
                                    entity=entity,
                                    goal=goal)
        elif task_type == ID.AI_TASK_TYPE_IDLE:
            parser = IdleTaskParser(type=task_type,
                                    variance_min=config.variance_min,
                                    variance_max=config.variance_max,
                                    prev_task=prev_task,
                                    entity=entity,
                                    duration=config.duration)
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
        else:
            raise UnknownTaskException('Task id "{0}" is unknown.'.format(task.type))
        return parser