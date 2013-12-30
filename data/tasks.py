import heapq

class TaskType:
    NEW_TASK_OR_IDLE = 0

class Task:
    """ Represents a single task. An object of this class may have more members
    based on the type of task.

    Member:
    appointee -- The object which must execute this task.
    type -- Type of task (TaskType).
    """

    def __init__(self, type, appointee):
        self.type = type
        self.appointee = appointee

class TaskList:
    """ List of tasks.

    Member:
    _tasks -- The task list implementation (list).
    """

    def __init__(self):
        self._tasks = []

    def insert(self, time, task):
        """ Insert new task into list. Time defines after which point in time the
         task is due. """
        item = (time, task)
        heapq.heappush(self._tasks, item)

    def take(self, time):
        """ Returns a list of all tasks which are due at the given point in time.
        This removes the tasks from the list. """
        result = []
        while self._tasks and self._tasks[0][0] <= time:
            item = heapq.heappop(self._tasks)
            result.append(item[1])
        return result