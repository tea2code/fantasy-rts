import logging
import random
from abc import abstractmethod

from ai import pathfinding
from data.ai.task import GoToTask, IdleTask
from data.config import ID
from data.world.entity.movable import Direction


class TaskParameterException(Exception):
    """ Raised if not all parameters are given. """


class BaseTaskParser():
    """ Base class for task parser. A parser should only be used for a single
    task.

    Member:
    entity -- The entity which is executing the task (data.world.entity.entity).
    prev_task -- The previous executed task (data.ai.task).
    task -- The currently executed task (data.ai.task).
    type -- The type of task (string).
    variance_max -- The max duration variance (float).
    variance_min -- The min duration variance (float).
    """

    def __init__(self, type=None, variance_min=None, variance_max=None,
                 prev_task=None, entity=None, task=None):
        """ You must give the task parameter or all the others. """
        if task:
            self.entity = task.entity
            self.prev_task = task.prev_task
            self.task = task
            self.type = task.type
        elif type and variance_min is not None and variance_max is not None and entity:
            self.entity = entity
            self.prev_task = prev_task
            self.type = type
            self.variance_max = variance_max
            self.variance_min = variance_min
        else:
            template = 'Not all expected parameters are given: ' \
                       'type={0}, variance_min={1}, variance_max={2}, ' \
                       'prev_task={3}, entity={4}, task={5}'
            msg = template.format(type, variance_min, variance_max, prev_task,
                                  entity, task)
            raise TaskParameterException(msg)

    @abstractmethod
    def create_new(self, data):
        """ Creates a new task and returns it. """

    @abstractmethod
    def execute_next(self, data):
        """ Execute next step in task on data. """

    @abstractmethod
    def is_complete(self):
        """ Returns true if task is complete else false. """

    @abstractmethod
    def is_success(self):
        """ Returns true if task is successful else false. """

    @abstractmethod
    def time(self):
        """ Returns the execution time in seconds of the current step. After
        this time the next step can be executed. """


class GoToTaskParser(BaseTaskParser):
    """ Parses go to tasks.

    Member:
    goal -- The goal to go to (data.world.point).
    """

    def __init__(self, type=None, variance_min=None, variance_max=None,
                 prev_task=None, entity=None, task=None, goal=None):
        super().__init__(type, variance_min, variance_max, prev_task, entity, task)
        self.goal = task.goal if task else goal

    def create_new(self, data):
        region = data.game.region
        start = region.get_pos(self.entity)
        path = self.__find_path(start, self.goal, self.entity.blocked, data.game.region)

        if path is None:
            self.__log_no_path(start, self.goal)
            time_per_step = 0.0
        else:
            # Calculate time for one step. Currently only walking is supported.
            time = 1.0 + random.uniform(self.variance_min, self.variance_max)
            time_per_step = time / self.entity.moving[ID.ENTITY_ATTRIBUTE_MOVING_WALK]

        self.task = GoToTask(self.type, self.prev_task, self.entity, self.goal,
                             path, time_per_step)
        return self.task

    def execute_next(self, data):
        region = data.game.region
        last_pos = region.get_pos(self.entity)
        pos = self.task.path.pop(0)
        if region.get_block(pos).is_blocking(self.entity.blocked):
            self.task.path = self.__find_path(last_pos, self.goal, self.entity.blocked, region)
            if self.task.path is None:
                self.__log_no_path(last_pos, self.goal)
                self.entity.direction = Direction.STOP
                return
            else:
                pos = self.task.path.pop(0)
        region.set_pos(self.entity, pos)

        self.entity.direction = pos - last_pos
        if not self.task.path:
            self.entity.direction = Direction.STOP

        data.dirty_pos.add(last_pos)
        data.dirty_pos.add(pos)

    def is_complete(self):
        return not self.task.path

    def is_success(self):
        return self.is_complete() and isinstance(self.task.path, list)

    def time(self):
        return self.task.time_per_step

    def __find_path(self, start, goal, blocked, region):
        """ Find path to target. """
        distance = pathfinding.EuclideanDistance()
        algorithm = pathfinding.AStar(distance)
        return algorithm.shortest_path(start, goal, blocked, region)

    def __log_no_path(self, start, goal):
        """ Log that no path is found. """
        logger = logging.getLogger(__name__)
        logger.info('No path found from {0} to {1}.'.format(start, goal))


class IdleTaskParser(BaseTaskParser):
    """ Parses idle tasks.

    Member:
    duration -- The idle duration (float).
    """

    def __init__(self, type=None, variance_min=None, variance_max=None,
                 prev_task=None, entity=None, task=None, duration=None):
        super().__init__(type, variance_min, variance_max, prev_task, entity, task)
        self.duration = task.duration if task else duration

    def create_new(self, data):
        if isinstance(self.duration, list):
            if self.prev_task and self.prev_task.type == self.type:
                durations = self.duration
                self.duration = durations[-1]
                for index, duration in enumerate(durations[:-1]):
                    if duration + self.variance_min <= self.prev_task.duration <= duration + self.variance_max:
                        self.duration = durations[index + 1]
            else:
                self.duration = self.duration[0]
        self.duration = self.duration + random.uniform(self.variance_min, self.variance_max)
        self.task = IdleTask(self.type, self.prev_task, self.entity, self.duration)
        return self.task

    def execute_next(self, data):
        pass

    def is_complete(self):
        return True

    def is_success(self):
        return True

    def time(self):
        return self.duration