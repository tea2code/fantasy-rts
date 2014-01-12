import random
import time

from . import flatregiongenerator
from data.world import region
from general import factory


class Demo:
    """ Creates a repeatable demo game.

    Constants:
    TIME_BURNER -- If not None the application will sleep every frame for the given time (float/None).

    Member:
    data -- The data object (data.data).
    _static_entity_count -- Number of static entities (int).
    """

    TIME_BURNER = None

    def __init__(self, data):
        self.data = data
        self._static_entity_count = 0

    def load(self):
        """ Loads the game into the data object. """
        # Create level map.
        region_generator = flatregiongenerator.FlatRegionGenerator(self.data)
        self.data.game.region = region.Region(region_generator, self.data.game.size_x, self.data.game.size_y)

        # Add creatures.
        num_x = 20
        num_y = num_x
        for x in range(1, num_x):
            for y in range(1, num_y):
                factory.new_creature(self.data, x, y, 0)

    def tick(self, run_time, delta_time, data):
        if self._static_entity_count < 10 and run_time % 1 <= delta_time:
            # Create new shrub.
            id = 'entity.static.berry-shrub'
            pos = data.game.region.free_random_pos(data.config.entity.statics[id].blocked, 0)
            s = factory.new_static_entity(data, id, pos=pos)

        # Burn additional time.
        if self.TIME_BURNER:
            time.sleep(self.TIME_BURNER)