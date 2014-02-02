import logging
import random

from . import basetask
from ai import pathfinding
from data.config import ID
from data.world.entity.movable import Direction

class GoToTask(basetask.BaseTask):
    """ Task which navigates a movable entity to a target.

    Member:
    goal -- The goal to go to (data.world.point).
    path -- The path to the target (list).
    time_per_step -- Time to go to the next position in the path (float).
    _complete -- Indicates that the task is complete (bool).
    """

    def __init__(self, entity, goal, data, variance_min, variance_max):
        super().__init__(entity, variance_min, variance_max)
        self.goal = goal

        region = data.game.region
        start = region.get_pos(entity)
        self.path = self.__find_path(start, goal, entity.blocked, data.game.region)

        if not self.path:
            self.__log_no_path(start, goal)
            self.time_per_step = 0.0
            self._complete = True
        else:
            # Calculate time for one step. Currently only walking is supported.
            self.time_per_step = 1.0 / entity.moving[ID.ENTITY_ATTRIBUTE_MOVING_WALK]
            self._complete = False

    def is_complete(self):
        return self._complete

    def execute_next(self, data):
        if not self.path:
            self._complete = True
            return

        region = data.game.region
        last_pos = region.get_pos(self.entity)
        pos = self.path.pop(0)
        if region.get_block(pos).is_blocking(self.entity.blocked):
            self.path = self.__find_path(last_pos, self.goal, self.entity.blocked, region)
            if not self.path:
                self.__log_no_path(last_pos, self.goal)
                self.entity.direction = Direction.STOP
                self._complete = True
            else:
                pos = self.path.pop(0)
        region.set_pos(self.entity, pos)

        self.entity.direction = pos - last_pos
        data.dirty_pos.add(last_pos)
        data.dirty_pos.add(pos)

        more = any(self.path)
        if not more:
            self.entity.direction = Direction.STOP
            self._complete = True
        else:
            self._complete = False

    def time(self):
        return self.time_per_step

    def __find_path(self, start, goal, blocked, region):
        """ Find path to target. """
        distance = pathfinding.EuclideanDistance()
        algorithm = pathfinding.AStar(distance)
        return algorithm.shortest_path(start, goal, blocked, region)

    def __log_no_path(self, start, goal):
        """ Log that no path is found. """
        logger = logging.getLogger(__name__)
        logger.info('No path found from {0} to {1}.'.format(start, goal))