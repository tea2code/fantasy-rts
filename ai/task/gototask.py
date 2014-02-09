import random
import logging

from . import basetask
from .. import pathfinding
from data.ai.task import GoToTask
from data.config import ID
from data.world.entity.movable import Direction


class GoToTaskParser(basetask.BaseTaskParser):
    """ Parses go to tasks.

    Member:
    goal -- The goal to go to (data.world.point).
    """

    def __init__(self, type=None, variance_min=None, variance_max=None,
                 prev_task=None, entity=None, task=None, goal=None):
        super().__init__(type, variance_min, variance_max, prev_task, entity, task)
        self.goal = task.goal if task else goal

    def cleanup(self, data):
        pass

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