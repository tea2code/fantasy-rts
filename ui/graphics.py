import pygame

from . import spriteloader
from data import direction
from data import point

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
        self._sprite_loader = spriteloader.PygameSpriteLoader(data)

        self.__calc_view_offset(graphics.view_offset_x, graphics.view_offset_y)
        self.__show_title(graphics.window_title)
        self.__draw_background(data)
        pygame.display.flip()

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

    def __draw_pos(self, pos, data, move_point=True):
        game = data.game
        graphics = data.graphics
        x, y = self.__pos_to_screen(pos, graphics.tile)
        if move_point:
            pos += self._view_offset_point
        level_tile = game.level[pos] if pos in game.level else game.level.default_tile
        sprite_img, tile_sprite = self._sprite_loader.sprite_by_tile(level_tile)
        self.screen.blit(sprite_img, (x, y), tile_sprite)
        return x, y, graphics.tile, graphics.tile

    def __pos_to_screen(self, pos, tile):
        return int(pos.x * tile), int(pos.y * tile)

    def __show_title(self, window_title):
        fps = self.clock.get_fps()
        text = window_title.format(fps)
        pygame.display.set_caption(text)

    def __update_screen(self, data):
        game = data.game
        graphics = data.graphics

        dirty_rects = []
        dirty_pos = []

        # First render tile.
        if graphics.view_updated:
            self.__calc_view_offset(graphics.view_offset_x, graphics.view_offset_y)
            self.__draw_background(data)
        else:
            for pos in data.dirty_pos:
                if self.__visible(pos, graphics):
                    rect = self.__draw_pos(pos, data, False)
                    dirty_rects.append(rect)
                    dirty_pos.append(pos)

        # Render world objects.
        for obj in game.world:
            if not graphics.view_updated and obj.pos not in dirty_pos:
                continue
            pos = obj.pos - self._view_offset_point
            xy = self.__pos_to_screen(pos, graphics.tile)
            sprite_img, sprite = self._sprite_loader.world_sprite_by_obj(obj)
            self.screen.blit(sprite_img, xy, sprite)

        # At last render creatures.
        for creature in game.creatures:
            if not graphics.view_updated and creature.pos not in dirty_pos:
                continue
            pos = creature.pos - self._view_offset_point
            xy = self.__pos_to_screen(pos, graphics.tile)
            dir = creature.direction if creature.direction != direction.STOP else creature.last_direction
            sprite_img, sprite = self._sprite_loader.creature_sprite_by_dir(dir)
            self.screen.blit(sprite_img, xy, sprite)

        if graphics.view_updated:
            pygame.display.flip()
        else:
            pygame.display.update(dirty_rects)

    def __visible(self, pos, graphics):
        return graphics.view_offset_x <= pos.int_x < graphics.view_offset_x + graphics.view_x and \
               graphics.view_offset_y <= pos.int_y < graphics.view_offset_y + graphics.view_y