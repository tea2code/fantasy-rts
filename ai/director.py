from . import decision
from .task import factory as task_parser


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
            parser = task_parser.Factory.from_task(task)
            if not parser.is_complete():
                parser.execute_next(data)
            if parser.is_complete():
                parser.cleanup(data)
                task_id, pipeline = self.decision_tree.parse(task.entity,
                                                             data.game.decision_tree,
                                                             parser.is_success())
                self.__new_task(task_id, task, run_time, data, pipeline)
            else:
                self.__add_task(parser, task, run_time, data)

    def __add_task(self, parser, task, run_time, data):
        """ Add task to task list. """
        time = run_time + parser.time()
        data.game.tasks.insert(time, task)

    def __new_task(self, task_id, prev_task, run_time, data, pipeline):
        """ Create new task and add to task list. """
        parser = task_parser.Factory.from_id(task_id, prev_task, data, pipeline=pipeline)
        task = parser.create_new(data)
        self.__add_task(parser, task, run_time, data)