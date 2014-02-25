import logging
import sys

import pygame

from . import helper
from .keys import PygameKeys
from data import id as ID
from data.world import point


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
                logger.info('Run Time = {0:.2f}s; FPS = {1:.2f}'.format(run_time, sum(data.fps) / len(data.fps)))
                sys.exit()
            elif event.type == pygame.KEYDOWN:
                data.input.keys_pressed.append(event.key)
            elif event.type == pygame.KEYUP:
                data.input.keys_pressed.remove(event.key)
            elif event.type == pygame.MOUSEBUTTONDOWN:
                data.input.mouse_pressed = True
            elif event.type == pygame.MOUSEBUTTONUP:
                data.input.mouse_pressed = False

        if data.input.mouse_pressed:
            self.__mouse_down(data)

        if data.input.next_key_execution < run_time:
            for key in data.input.keys_pressed:
                self.__key_down(key, data)
            data.input.next_key_execution += 0.1

    def __key_down(self, key, data):
        """ Handle key down events. """
        config = data.config
        game = data.game
        graph = data.graphics

        # Cursor
        if key == self._keys[ID.ACTION_CURSOR_NORTH]:
            self.__move_cursor(data, point.Factory.new_point(0, -1, 0))
        elif key == self._keys[ID.ACTION_CURSOR_SOUTH]:
            self.__move_cursor(data, point.Factory.new_point(0, +1, 0))
        elif key == self._keys[ID.ACTION_CURSOR_WEST]:
            self.__move_cursor(data, point.Factory.new_point(-1, 0, 0))
        elif key == self._keys[ID.ACTION_CURSOR_EAST]:
            self.__move_cursor(data, point.Factory.new_point(+1, 0, 0))

        # Scrolling
        elif key == self._keys[ID.ACTION_SCROLL_NORTH]:
            graph.view_offset_y = max(graph.view_offset_y - config.scroll_width_y,
                                      0)
            graph.view_updated = True
        elif key == self._keys[ID.ACTION_SCROLL_SOUTH]:
            graph.view_offset_y = min(graph.view_offset_y + config.scroll_width_y,
                                      game.size_y - graph.view_y)
            graph.view_updated = True
        elif key == self._keys[ID.ACTION_SCROLL_WEST]:
            graph.view_offset_x = max(graph.view_offset_x - config.scroll_width_x,
                                      0)
            graph.view_updated = True
        elif key == self._keys[ID.ACTION_SCROLL_EAST]:
            graph.view_offset_x = min(graph.view_offset_x + config.scroll_width_x,
                                      game.size_x - graph.view_x)
            graph.view_updated = True

    def __mouse_down(self, data):
        """ Handle mouse down events. """
        graphics = data.graphics
        screen_pos = pygame.mouse.get_pos()
        x, y = helper.screen_to_pos(point.Factory.new_point(screen_pos[0], screen_pos[1], 0),
                                    graphics.tile_x, graphics.tile_y)
        data.dirty_pos.add(graphics.cursor)
        graphics.cursor = point.Factory.new_point(x + graphics.view_offset_x,
                                                  y + graphics.view_offset_y,
                                                  0)
        data.dirty_pos.add(graphics.cursor)

    def __move_cursor(self, data, direction):
        """ Moves cursor in direction. """
        data.dirty_pos.add(data.graphics.cursor)
        data.graphics.cursor += direction
        data.dirty_pos.add(data.graphics.cursor)