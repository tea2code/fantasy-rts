import logging

from . import basetask
from ai import pathfinding
from data.config import ID

class GoToTask(basetask.BaseTask):
    """ Task which navigates a movable entity to a target.

    Member:
    path -- The path to the target (list).
    time_per_step -- Time to go to the next position in the path (float).
    """

    def __init__(self, entity, goal, data):
        super().__init__(entity)

        # Find path to target.
        region = data.game.region
        start = region.get_pos(entity)
        distance = pathfinding.EuclideanDistance()
        algorithm = pathfinding.AStar(distance)
        self.path = algorithm.shortest_path(start, goal, entity.blocked, region)
        if not self.path:
            logger = logging.getLogger(__name__)
            logger.info('No path found from {0} to {1}.'.format(start, goal))

        # Calculate time for one step. Currently only walking is supported.
        self.time_per_step = 1.0 / entity.moving[ID.ENTITY_ATTRIBUTE_MOVING_WALK]

    def execute_next(self, data):
        if not self.path:
            return False
        last_pos = data.game.region.get_pos(self.entity)
        pos = self.path.pop(0)
        data.game.region.set_pos(self.entity, pos)
        data.dirty_pos.add(last_pos)
        data.dirty_pos.add(pos)
        return any(self.path)

    def time(self):
        return self.time_per_step