class BaseTask:
    """ Base class for all tasks.

    Member:
    entity -- The entity which executes this task (data.world.entity).
    _sub_tasks -- List of sub tasks (list).
    """

    def __init__(self, entity):
        self.entity = entity
        self._sub_tasks = []

    def execute_next(self, data):
        """ Execute next step in task on data. Returns true if more steps
        are necessary else false. """
        return False

    def time(self):
        """ Returns the execution time in seconds of the current step. After
        this time the next step can be executed. """
        return 0.0