class Ai:
    """ They ai config.

    Member:
    tasks -- Mapping of task id to task config (dict).
    """

    def __init__(self):
        self.tasks = {}


class BaseTask:
    """ Base class for task config.

    Member:
    type -- Id of the type (string).
    variance_max -- The maximum time variance (float).
    variance_min -- The minimum time variance (float).
    """

    def __init__(self, type, variance_min, variance_max):
        self.type = type
        self.variance_max = variance_max
        self.variance_min = variance_min


class GoToTask(BaseTask):
    """ Config for go to tasks. """

    def __init__(self, type, variance_min, variance_max):
        super().__init__(type, variance_min, variance_max)

class IdleTask(BaseTask):
    """ Config for idle tasks.

    Member:
    duration -- The duration as a single float or a list of floats (float/list).
    """

    def __init__(self, type, variance_min, variance_max, duration):
        super().__init__(type, variance_min, variance_max)
        self.duration = duration