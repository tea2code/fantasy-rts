from abc import abstractmethod


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

    def __init__(self, type=None, variance_min=None, variance_max=None,
                 prev_task=None, entity=None, input=None, output=None,
                 pipeline=None, task=None):
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
        elif type and variance_min is not None and variance_max is not None and entity:
            self.entity = entity
            self.prev_task = prev_task
            if prev_task:
                prev_task.prev_task = None
            self.type = type
            self.variance_max = variance_max
            self.variance_min = variance_min
            self.input = input
            self.output = output
            self.pipeline = pipeline if pipeline else {}
        else:
            template = 'Not all expected parameters are given: ' \
                       'type={0}, variance_min={1}, variance_max={2}, ' \
                       'prev_task={3}, entity={4}, input={5}, output={6},' \
                       'pipeline={7}, task={8}'
            msg = template.format(type, variance_min, variance_max, prev_task,
                                  entity, input, output, pipeline, task)
            raise TaskParameterException(msg)

    @abstractmethod
    def cleanup(self, data):
        """ Clean up after task completion. """

    @abstractmethod
    def create_new(self, data):
        """ Creates a new task and returns it. """

    @abstractmethod
    def execute_next(self, data):
        """ Execute next step in task on data. """

    @abstractmethod
    def is_complete(self):
        """ Returns true if task is complete else false. """

    @abstractmethod
    def is_success(self):
        """ Returns true if task is successful else false. """

    @abstractmethod
    def time(self):
        """ Returns the execution time in seconds of the current step. After
        this time the next step can be executed. """