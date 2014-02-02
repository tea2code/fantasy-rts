import logging
import pygame
import sys

from data.config import ID
from .keys import PygameKeys

class PygameEventHandler:
    """ Handles pygame events.

    Member:
    _keys -- Mapping of action to keys (dict).
    """

    def __init__(self, data):
        self._keys = {}
        for id in ID._ACTION_SCROLL:
            self._keys[id] = PygameKeys.MAP[data.config.keys[id].key]

    def tick(self, run_time, delta_time, data, tick):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                logger = logging.getLogger(__name__)
                logger.info('Run Time = {0:.2f}; FPS = {1:.2f}s'.format(run_time, sum(data.fps) / len(data.fps)))
                sys.exit()
            elif event.type == pygame.KEYDOWN:
                self.__keydown(event, data)

    def __keydown(self, event, data):
        config = data.config
        game = data.game
        graph = data.graphics

        # Scrolling
        if event.key == self._keys[ID.ACTION_SCROLL_NORTH]:
            graph.view_offset_y = max(graph.view_offset_y - config.scroll_width_y,
                                      0)
            graph.view_updated = True
        elif event.key == self._keys[ID.ACTION_SCROLL_SOUTH]:
            graph.view_offset_y = min(graph.view_offset_y + config.scroll_width_y,
                                      game.size_y - graph.view_y)
            graph.view_updated = True
        elif event.key == self._keys[ID.ACTION_SCROLL_WEST]:
            graph.view_offset_x = max(graph.view_offset_x - config.scroll_width_x,
                                      0)
            graph.view_updated = True
        elif event.key == self._keys[ID.ACTION_SCROLL_EAST]:
            graph.view_offset_x = min(graph.view_offset_x + config.scroll_width_x,
                                      game.size_x - graph.view_x)
            graph.view_updated = True