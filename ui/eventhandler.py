import logging
import pygame
import sys

class PygameEventHandler:
    """ Handles pygame events. """

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
        if event.key == pygame.K_UP:
            graph.view_offset_y = max(graph.view_offset_y - config.scroll_width_y,
                                      0)
        elif event.key == pygame.K_DOWN:
            graph.view_offset_y = min(graph.view_offset_y + config.scroll_width_y,
                                      game.size_y - graph.view_y)
        elif event.key == pygame.K_LEFT:
            graph.view_offset_x = max(graph.view_offset_x - config.scroll_width_x,
                                      0)
        elif event.key == pygame.K_RIGHT:
            graph.view_offset_x = min(graph.view_offset_x + config.scroll_width_x,
                                      game.size_x - graph.view_x)
        graph.view_updated = True