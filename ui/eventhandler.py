import pygame
import sys

class PygameEventHandler:
    """ Handles pygame events. """

    def tick(self, run_time, delta_time, data):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                sys.exit()
            elif event.type == pygame.KEYDOWN:
                self.__keydown(event, data)

    def __keydown(self, event, data):
        game = data.game
        graph = data.graphics
        if event.key == pygame.K_UP:
            graph.view_offset_y = max(graph.view_offset_y - graph.scroll_width,
                                      0)
        elif event.key == pygame.K_DOWN:
            graph.view_offset_y = min(graph.view_offset_y + graph.scroll_width,
                                      game.tile_y - graph.view_y)
        elif event.key == pygame.K_LEFT:
            graph.view_offset_x = max(graph.view_offset_x - graph.scroll_width,
                                      0)
        elif event.key == pygame.K_RIGHT:
            graph.view_offset_x = min(graph.view_offset_x + graph.scroll_width,
                                      game.tile_x - graph.view_x)
        graph.view_updated = True