class Cleaner:
    """ Resets frame specific variables. """

    def tick(self, run_time, delta_time, data):
        data.dirty_pos = []
        data.graphics.view_updated = False