import logging
import sys
import time

from . import flatregiongenerator
from data.world import factory, region


class Demo:
    """ Creates a repeatable demo game.

    Constants:
    TIME_BURNER -- If not None the application will sleep every frame for the given time (float/None).

    Member:
    data -- The data object (data.data).
    """

    RUN_TIME = 10 * 60
    TIME_BURNER = None

    def __init__(self, data):
        self.data = data

    def load(self):
        """ Loads the game into the data object. """
        # Create level map.
        #region_generator = mazeregiongenerator.MazeRegionGenerator(self.data)
        region_generator = flatregiongenerator.FlatRegionGenerator(self.data)
        self.data.game.region = region.Region(region_generator, self.data.game.size_x, self.data.game.size_y)

        # Add creatures.
        run_time = 0
        num_x = 10
        num_y = 20
        for x in range(1, num_x + 1):
            for y in range(1, num_y + 1):
                factory.new_add_dynamic_entity(self.data.game.race_player, self.data, run_time, x, y, z=0)

    def tick(self, run_time, delta_time, data, tick):
        # Burn additional time.
        if self.TIME_BURNER:
            time.sleep(self.TIME_BURNER)

        # Stop game?
        if self.RUN_TIME and run_time >= self.RUN_TIME:
            logger = logging.getLogger(__name__)
            logger.info('Run Time = {0:.2f}s; FPS = {1:.2f}'.format(run_time, sum(data.fps) / len(data.fps)))
            sys.exit()