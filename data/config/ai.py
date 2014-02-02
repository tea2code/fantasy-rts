class Task:
    """ A task config.

    Member:
    type -- Id of the type (string).
    parameters -- Mapping of parameters (dict).
    variance_max -- The maximum time variance (float).
    variance_min -- The minimum time variance (float).
    """

    def __init__(self, type):
        self.type = type
        self.parameters = {}
        variance_max = 0.0
        variance_min = 0.0