from . import basetask
from ai import pathfinding

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

        # Calculate time for one step.
        self.time_per_step = 1.0 / entity.moving[0].speed

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