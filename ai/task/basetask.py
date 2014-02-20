from abc import abstractmethod
from data.ai.task import BaseTaskParameter


class PipelineParameterException(Exception):
    """ Raised if a necessary pipeline parameter is not set. """


class TaskParameterException(Exception):
    """ Raised if not all parameters are given. """


class BaseTaskParser:
    """ Base class for task parser. A parser should only be used for a single
    task.

    Member:
    entity -- The entity which is executing the task (data.world.entity.entity).
    input -- The key of the input value in the pipeline (string).
    output -- The key of the output value in the pipeline (string).
    pipeline -- The pipeline parameter object (dict).
    prev_task -- The previous executed task (data.ai.task).
    task -- The currently executed task (data.ai.task).
    type -- The type of task (string).
    variance_max -- The max duration variance (float).
    variance_min -- The min duration variance (float).
    """

    def __init__(self, base_task_parameter=None, variance_min=None,
                 variance_max=None, task=None):
        """ You must give the task parameter or all the others. """
        if task:
            self.entity = task.entity
            self.prev_task = task.prev_task
            if task.prev_task and task.prev_task.prev_task:
                task.prev_task.prev_task = None
            self.task = task
            self.type = task.type
            self.input = task.input
            self.output = task.output
            self.pipeline = task.pipeline if task.pipeline else {}
        elif base_task_parameter.type and variance_min is not None and \
             variance_max is not None and \
             base_task_parameter.entity:
            self.entity = base_task_parameter.entity
            self.prev_task = base_task_parameter.prev_task
            if base_task_parameter.prev_task:
                # Remove previous task of previous task to prevent memory leak.
                base_task_parameter.prev_task.prev_task = None
            self.type = base_task_parameter.type
            self.variance_max = variance_max
            self.variance_min = variance_min
            self.input = base_task_parameter.input
            self.output = base_task_parameter.output
            self.pipeline = base_task_parameter.pipeline if base_task_parameter.pipeline else {}
        else:
            template = 'Not all expected parameters are given: ' \
                       'type={0}, variance_min={1}, variance_max={2}, ' \
                       'prev_task={3}, entity={4}, input={5}, output={6},' \
                       'pipeline={7}, task={8}'
            msg = template.format(base_task_parameter.type, variance_min, variance_max,
                                  base_task_parameter.prev_task,
                                  base_task_parameter.entity, base_task_parameter.input,
                                  base_task_parameter.output, base_task_parameter.pipeline,
                                  task)
            raise TaskParameterException(msg)

    @abstractmethod
    def create_new(self, data):
        """ Creates a new task and returns it. """

    def execute_next(self, data):
        """ Execute next step in task on data. """

    def is_complete(self):
        """ Returns true if task is complete else false. """
        return True

    @abstractmethod
    def is_success(self):
        """ Returns true if task is successful else false. """

    def time(self):
        """ Returns the execution time in seconds of the current step. After
        this time the next step can be executed. """
        return 0.0

    def base_task_parameter(self):
        """ Returns the base task parameter of this parser. """
        base_task_parameter = BaseTaskParameter()
        base_task_parameter.type = self.type
        base_task_parameter.prev_task = self.prev_task
        base_task_parameter.entity = self.entity
        base_task_parameter.input = self.input
        base_task_parameter.output = self.output
        base_task_parameter.pipeline = self.pipeline
        return base_task_parameter