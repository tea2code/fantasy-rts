class RenderCleaner:
    """ Resets frame specific variables. """

    def tick(self, run_time, delta_time, data, tick):
        data.dirty_pos = set()
        data.game.events = []
        data.graphics.view_updated = False