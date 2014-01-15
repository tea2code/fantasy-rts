from . import basetask

class IdleTask(basetask.BaseTask):
    """ A task for entities which should idle. """

    def __init__(self, entity):
        super().__init__(entity)