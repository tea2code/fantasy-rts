from . import decision
from . import task as taskparser
from data.config import ID


class UnknownTaskException(Exception):
    """ Raised if a unknown task id is given. """


class Director:
    """ The AI director manages all behaviour.

    Member:
    decision_tree -- Parser for decision tree (ai.decision).
    """

    def __init__(self):
        self.decision_tree = decision.DecisionTreeParser()

    def tick(self, run_time, delta_time, data, tick):
        for task in data.game.tasks.take(run_time):
            parser = self.__task_parser(task)
            if not parser.is_complete():
                parser.execute_next(data)
            if parser.is_complete():
                task_id = self.decision_tree.parse(task.entity, data.game.decision_tree, parser.is_success())
                self.__new_task(task_id, task, run_time, data)
            else:
                self.__add_task(parser, task, run_time, data)

    def __add_task(self, parser, task, run_time, data):
        """ Add task to task list. """
        time = run_time + parser.time()
        data.game.tasks.insert(time, task)

    def __new_task(self, task_id, prev_task, run_time, data):
        """ Create new task and add to task list. """
        config = data.config.ai.tasks[task_id]
        task_type = config.type
        if task_type == ID.TASK_TYPE_RANDOM_GOTO:
            goal = data.game.region.free_random_pos(prev_task.entity.blocked, 0)
            parser = taskparser.GoToTaskParser(type=task_type,
                                               variance_min=config.variance_min,
                                               variance_max=config.variance_max,
                                               prev_task=prev_task,
                                               entity=prev_task.entity,
                                               goal=goal)
        elif task_type == ID.TASK_TYPE_IDLE:
            parser = taskparser.IdleTaskParser(type=task_type,
                                               variance_min=config.variance_min,
                                               variance_max=config.variance_max,
                                               prev_task=prev_task,
                                               entity=prev_task.entity,
                                               duration=config.parameters[ID.TASK_PARAMETER_TIME])
        else:
            raise UnknownTaskException('Task type "{0}" is unknown.'.format(task_type))
        task = parser.create_new(data)
        self.__add_task(parser, task, run_time, data)

    def __task_parser(self, task):
        """ Finds the parser for the given task. """
        if task.type == ID.TASK_TYPE_RANDOM_GOTO:
            parser = taskparser.GoToTaskParser(task=task)
        elif task.type == ID.TASK_TYPE_IDLE:
            parser = taskparser.IdleTaskParser(task=task)
        else:
            raise UnknownTaskException('Task id "{0}" is unknown.'.format(task.type))
        return parser