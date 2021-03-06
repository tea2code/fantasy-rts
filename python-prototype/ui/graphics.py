from collections import deque

import pygame

from . import helper, spriteloader
from data.world.point import Factory as PointFactory


class PygameGraphics:
    """ Graphical representation of state using pygame.

    Member:
    clock -- The pygame clock.
    screen -- The pygame surface which acts as the game screen.
    _fps -- List of last frames per second results (deque).
    _sprite_loader -- The sprite loader (ui.spriteloader).
    _view_offset_point -- The cached view offset point (point.Point).
    """

    def __init__(self, data):
        graphics = data.graphics

        size = (graphics.view_x * graphics.tile_x, graphics.view_y * graphics.tile_y)
        self.screen = pygame.display.set_mode(size)
        self.clock = pygame.time.Clock()
        self._fps = deque(maxlen=data.config.num_fps_avg)
        self._sprite_loader = spriteloader.PygameSpriteLoader(data)

        self.__calc_view_offset(graphics.view_offset_x, graphics.view_offset_y)
        self.__show_title(data)
        self.__draw_background(data)
        pygame.display.flip()

    def tick(self, run_time, delta_time, data, tick):
        # Update screen.
        self.__update_screen(data)

        # Show title and update clock.
        self.__show_title(data)
        self.clock.tick(data.config.fps) # Prevent unnecessary cpu load.

    def __calc_view_offset(self, view_offset_x, view_offset_y):
        """ Calculate view offset point. """
        self._view_offset_point = PointFactory.new_point(view_offset_x, view_offset_y)

    def __draw_background(self, data):
        graphics = data.graphics
        for x in range(graphics.view_offset_x, graphics.view_offset_x + graphics.view_x):
            for y in range(graphics.view_offset_y, graphics.view_offset_y + graphics.view_y):
                pos = PointFactory.new_point(x, y)
                self.__draw_pos(pos, data)

    def __draw_entities(self, entities, x, y, tile_x, tile_y):
        for entity in entities:
            sprite_img, sprite_x, sprite_y = self._sprite_loader.get_sprite(entity)
            self.screen.blit(sprite_img, (x, y), (sprite_x, sprite_y, tile_x, tile_y))

    def __draw_pos(self, pos, data):
        game = data.game
        graphics = data.graphics

        block = game.region.get_block(pos)
        x, y = helper.pos_to_screen(pos - self._view_offset_point, graphics.tile_x, graphics.tile_y)

        self.__draw_entities(block.get_tiles(), x, y, graphics.tile_x, graphics.tile_y)
        self.__draw_entities(block.get_statics(), x, y, graphics.tile_x, graphics.tile_y)
        self.__draw_entities(block.get_dynamics(), x, y, graphics.tile_x, graphics.tile_y)

        if pos == graphics.cursor:
            sprite_img, sprite_x, sprite_y = self._sprite_loader.get_sprite_by_id(data.config.style.cursor_mapping)
            self.screen.blit(sprite_img, (x, y), (sprite_x, sprite_y, graphics.tile_x, graphics.tile_y))

        return x, y, graphics.tile_x, graphics.tile_y

    def __show_title(self, data):
        fps = self.clock.get_fps()
        data.fps.append(fps)
        self._fps.append(fps)
        text = data.graphics.window_title.format(sum(self._fps) / len(self._fps))
        pygame.display.set_caption(text)

    def __update_screen(self, data):
        graphics = data.graphics

        dirty_rects = []

        if graphics.view_updated:
            self.__calc_view_offset(graphics.view_offset_x, graphics.view_offset_y)
            self.__draw_background(data)
        else:
            for pos in data.dirty_pos:
                if helper.is_visible(pos, graphics):
                    rect = self.__draw_pos(pos, data)
                    dirty_rects.append(rect)

        if graphics.view_updated:
            pygame.display.flip()
        else:
            pygame.display.update(dirty_rects)