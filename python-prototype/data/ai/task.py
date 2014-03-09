class BaseTask:
    """ Base class for tasks.

    Member:
    entity -- The entity which is executing this task (data.world.entity.entity).
    input -- The key of the input value in the pipeline (string/list).
    output -- The key of the output value in the pipeline (string/list).
    pipeline -- The pipeline parameter object (dict).
    prev_task -- The previous task (task).
    type -- The task type (string).
    """

    def __init__(self, base_task_parameter):
        self.type = base_task_parameter.type
        self.prev_task = base_task_parameter.prev_task
        self.entity = base_task_parameter.entity
        self.input = base_task_parameter.input
        self.output = base_task_parameter.output
        self.pipeline = base_task_parameter.pipeline

    def __lt__(self, other):
        """ No real implementation necessary. Only for heapq. """
        return True


class BaseTaskParameter:
    """ Class for common base task parameter.

    Member:
    entity -- The entity which is executing this task (data.world.entity.entity).
    input -- The key of the input value in the pipeline (string/list).
    output -- The key of the output value in the pipeline (string/list).
    pipeline -- The pipeline parameter object (dict).
    prev_task -- The previous task (task).
    type -- The task type (string).
    """

    def __init__(self):
        self.type = None
        self.prev_task = None
        self.entity = None
        self.input = None
        self.output = None
        self.pipeline = None


class GoToTask(BaseTask):
    """ A go to task.

    Member:
    goal -- The goal to go to (data.world.point).
    path -- The remaining path (list).
    time_per_step -- Duration of one step (float).
    """

    def __init__(self, base_task_parameter, goal, path, time_per_step):
        super().__init__(base_task_parameter)
        self.goal = goal
        self.path = path
        self.time_per_step = time_per_step


class IdleTask(BaseTask):
    """ A idle task.

     Member:
     duration -- The idle duration (float).
     """

    def __init__(self, base_task_parameter, duration):
        super().__init__(base_task_parameter)
        self.duration = duration
        

class SuccessTask(BaseTask):
    """ Simple tasks which only stores the success.
    
    Member:
    successful -- Indicates success of task (bool).
    """
    
    def __init__(self, base_task_parameter, successful):
        super().__init__(base_task_parameter)
        self.successful = successful