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

        size = (graphics.view_x * graphics.tile_x, graphics.view_y * graphics.tile_y)
        self.screen = pygame.display.set_mode(size)
        self.clock = pygame.time.Clock()
        self._sprite_loader = spriteloader.PygameSpriteLoader(data)

        self.__calc_view_offset(graphics.view_offset_x, graphics.view_offset_y)
        self.__show_title(graphics.window_title)
        self.__draw_background(data)
        pygame.display.flip()

    @staticmethod
    def pos_to_screen(pos, tile_x, tile_y):
        """ Convert world coordinates to tile position on screen. This
        returns the left upper corner.

        Test:
        >>> from data import point
        >>> p = point.Point(0, 0)
        >>> PygameGraphics.pos_to_screen(p, 16, 18)
        (0, 0)
        >>> p = point.Point(1, 2)
        >>> PygameGraphics.pos_to_screen(p, 16, 18)
        (16, 36)
        """
        return int(pos.x * tile_x), int(pos.y * tile_y)

    def tick(self, run_time, delta_time, data):
        # Update screen.
        self.__update_screen(data)

        # Show title and update clock.
        self.__show_title(data.graphics.window_title)
        self.clock.tick(data.config.fps) # Prevent unnecessary cpu load.

    @staticmethod
    def visible(pos, graphics):
        """ Checks if a position is visible on screen.

        Test:
        >>> from data import graphics
        >>> g = graphics.Graphics()
        >>> g.view_offset_x = 1
        >>> g.view_offset_y = 2
        >>> g.view_x = 5
        >>> g.view_y = 10
        >>> from data import point
        >>> p = point.Point(0, 0)
        >>> PygameGraphics.visible(p, g)
        False
        >>> p = point.Point(1, 1)
        >>> PygameGraphics.visible(p, g)
        False
        >>> p = point.Point(1, 2)
        >>> PygameGraphics.visible(p, g)
        True
        >>> p = point.Point(3, 7)
        >>> PygameGraphics.visible(p, g)
        True
        >>> p = point.Point(6, 7)
        >>> PygameGraphics.visible(p, g)
        False
        >>> p = point.Point(3, 12)
        >>> PygameGraphics.visible(p, g)
        False
        """
        return graphics.view_offset_x <= pos.int_x < graphics.view_offset_x + graphics.view_x and \
               graphics.view_offset_y <= pos.int_y < graphics.view_offset_y + graphics.view_y

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
        x, y = self.pos_to_screen(pos, graphics.tile_x, graphics.tile_y)
        if move_point:
            pos += self._view_offset_point
        level_tile = game.level[pos] if pos in game.level else game.level.default_tile
        sprite_img, tile_sprite = self._sprite_loader.sprite_by_tile(level_tile)
        self.screen.blit(sprite_img, (x, y), tile_sprite)
        return x, y, graphics.tile_x, graphics.tile_y

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
                if self.visible(pos, graphics):
                    rect = self.__draw_pos(pos, data, False)
                    dirty_rects.append(rect)
                    dirty_pos.append(pos)

        # Render world objects.
        for obj in game.world:
            if not graphics.view_updated and obj.pos not in dirty_pos:
                continue
            pos = obj.pos - self._view_offset_point
            xy = self.pos_to_screen(pos, graphics.tile_x, graphics.tile_y)
            sprite_img, sprite = self._sprite_loader.world_sprite_by_obj(obj)
            self.screen.blit(sprite_img, xy, sprite)

        # At last render creatures.
        for creature in game.creatures:
            if not graphics.view_updated and creature.pos not in dirty_pos:
                continue
            pos = creature.pos - self._view_offset_point
            xy = self.pos_to_screen(pos, graphics.tile_x, graphics.tile_y)
            dir = creature.direction if creature.direction != direction.STOP else creature.last_direction
            sprite_img, sprite = self._sprite_loader.creature_sprite_by_dir(dir)
            self.screen.blit(sprite_img, xy, sprite)

        if graphics.view_updated:
            pygame.display.flip()
        else:
            pygame.display.update(dirty_rects)

if __name__ == '__main__':
    print('Executing doctest.')
    import doctest
    doctest.testmod()