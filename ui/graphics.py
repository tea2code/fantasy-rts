import pygame

from . import spriteloader
from data import point
from data import tile

class PygameGraphics:
    """ Graphical representation of state using pygame.

    Member:
    clock -- The pygame clock.
    screen -- The pygame surface which acts as the game screen.
    _sprite_loader -- The sprite loader (ui.spriteloader).
    _view_offset_point -- The cached view offset point (point.Point).
    """

    def __init__(self, data):
        graphics = data.graphics

        size = (graphics.view_x * graphics.tile, graphics.view_y * graphics.tile)
        self.screen = pygame.display.set_mode(size)
        self.clock = pygame.time.Clock()
        self._sprite_loader = spriteloader.PygameSpriteLoader()
        self.sprite_img = self._sprite_loader.load(graphics.sprite)

        self.__calc_view_offset(graphics.view_offset_x, graphics.view_offset_y)
        self.__show_title(graphics.window_title)
        self.__draw_background(data)

    def tick(self, run_time, delta_time, data):
        # Show title and update clock.
        self.__show_title(data.graphics.window_title)
        self.clock.tick(data.graphics.fps) # Prevent unnecessary cpu load.

        # Update screen.
        self.__update_screen(data)

    def __calc_view_offset(self, view_offset_x, view_offset_y):
        """ Calculate view offset point. """
        self._view_offset_point = point.Point(view_offset_x, view_offset_y)

    def __draw_background(self, data):
        for x in range(data.graphics.view_x):
            for y in range(data.graphics.view_y):
                pos = point.Point(x, y)
                self.__draw_pos(pos, data)
        pygame.display.flip()

    def __draw_pos(self, pos, data):
        x, y = self.__pos_to_screen(pos, data.graphics.tile)
        rect = (x, y, data.graphics.tile, data.graphics.tile)
        pos = pos + self._view_offset_point
        level_tile = data.game.level[pos] if pos in data.game.level else data.game.level.default_tile
        tile_sprite = self._sprite_loader.sprite_by_tile(level_tile)
        self.screen.blit(self.sprite_img, (x, y), tile_sprite)
        return rect

    def __pos_to_screen(self, pos, tile):
        return int(pos.x * tile), int(pos.y * tile)

    def __show_title(self, window_title):
        fps = self.clock.get_fps()
        text = window_title.format(fps)
        pygame.display.set_caption(text)

    def __update_screen(self, data):
        graphics = data.graphics

        if graphics.view_updated:
            self.__calc_view_offset(graphics.view_offset_x, graphics.view_offset_y)
            self.__draw_background(data)

        if graphics.view_updated:
            pygame.display.flip()
            graphics.view_updated = False