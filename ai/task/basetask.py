class BaseTask:
    """ Base class for all tasks.

    Member:
    entity -- The entity which executes this task (data.world.entity).
    variance_max -- The maximum time variance (float).
    variance_min -- The minimum time variance (float).
    _sub_tasks -- List of sub tasks (list).
    """

    def __init__(self, entity, variance_min, variance_max):
        self.entity = entity
        self.variance_max = variance_max
        self.variance_min = variance_min
        self._sub_tasks = []

    def execute_next(self, data):
        """ Execute next step in task on data. """

    def is_complete(self):
        """ Returns true if task is complete else false. """
        return False

    def time(self):
        """ Returns the execution time in seconds of the current step. After
        this time the next step can be executed. """
        return 0.0

    def __lt__(self, other):
        """ No real implementation necessary. Only for heapq. """
        return True