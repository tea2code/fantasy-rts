from ai.task import gototask, idletask
from data.config import ID

class Factory:
    """ Factory for tasks. """

    @staticmethod
    def new_task(id, entity, data):
        """ Create new task. """
        config = data.config.tasks[id]
        id = config.type
        if id == ID.TASK_TYPE_RANDOM_GOTO:
            free_pos = data.game.region.free_random_pos(entity.blocked, 0)
            task = gototask.GoToTask(entity, free_pos, data, config.variance_min, config.variance_max)
        else:
            task = idletask.IdleTask(entity, config, config.variance_min, config.variance_max)
        return task