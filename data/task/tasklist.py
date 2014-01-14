import heapq

class TaskList:
    """ List of tasks.

    Member:
    _tasks -- The task list implementation (list).
    """

    def __init__(self):
        self._tasks = []

    def insert(self, time, task):
        """ Insert new task into list. Time defines after which point in time the
        task is due.
         Test:
        >>> t = TaskList()
        >>> t.insert(0.0, 'task1')
        >>> t.insert(1.0, 'task2')
        >>> t.insert(1.1, 'task3')
        >>> t.insert(2.0, 'task4')
        >>> t.take(0.1)
        ['task1']
        >>> t.take(1.9)
        ['task2', 'task3']
        >>> t.take(0.0)
        []
        >>> t.take(5.0)
        ['task4']
        """
        item = (time, task)
        heapq.heappush(self._tasks, item)

    def take(self, time):
        """ Returns a list of all tasks which are due at the given point in time.
        This removes the tasks from the list.

        Test: See insert().
        """
        result = []
        while self._tasks and self._tasks[0][0] <= time:
            item = heapq.heappop(self._tasks)
            result.append(item[1])
        return result

if __name__ == '__main__':
    print('Executing doctest.')
    import doctest
    doctest.testmod()