class BaseTask:
    """ Base class for tasks.

    Member:
    entity -- The entity which is executing this task (data.world.entity.entity).
    prev_task -- The previous task (task).
    type -- The task type (string).
    """

    def __init__(self, type, prev_task, entity):
        self.type = type
        self.prev_task = prev_task
        self.entity = entity

    def __lt__(self, other):
        """ No real implementation necessary. Only for heapq. """
        return True


class GoToTask(BaseTask):
    """ A go to task.

    Member:
    goal -- The goal to go to (data.world.point).
    path -- The remaining path (list).
    time_per_step -- Duration of one step (float).
    """

    def __init__(self, type, prev_task, entity, goal, path, time_per_step):
        super().__init__(type, prev_task, entity)
        self.goal = goal
        self.path = path
        self.time_per_step = time_per_step


class IdleTask(BaseTask):
    """ A idle task.

     Member:
     duration -- The idle duration (float).
     """

    def __init__(self, type, prev_task, entity, duration):
        super().__init__(type, prev_task, entity)
        self.duration = duration