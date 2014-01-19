import pygame

from . import spriteloader
from collections import deque
from data.world.point import Factory as PointFactory


class PygameGraphics:
    """ Graphical representation of state using pygame.

    Constants:
    MAX_FPS -- Maximum number of fps in list (int).

    Member:
    clock -- The pygame clock.
    screen -- The pygame surface which acts as the game screen.
    _fps -- List of last frames per second results (deque).
    _sprite_loader -- The sprite loader (ui.spriteloader).
    _view_offset_point -- The cached view offset point (point.Point).
    """

    MAX_FPS = 1000

    def __init__(self, data):
        graphics = data.graphics

        size = (graphics.view_x * graphics.tile_x, graphics.view_y * graphics.tile_y)
        self.screen = pygame.display.set_mode(size)
        self.clock = pygame.time.Clock()
        self._fps = deque(maxlen=self.MAX_FPS)
        self._sprite_loader = spriteloader.PygameSpriteLoader(data)

        self.__calc_view_offset(graphics.view_offset_x, graphics.view_offset_y)
        self.__show_title(data)
        self.__draw_background(data)
        pygame.display.flip()

    @staticmethod
    def pos_to_screen(pos, tile_x, tile_y):
        """ Convert world coordinates to tile position on screen. This
        returns the left upper corner.

        Test:
        >>> from data.world import point
        >>> p = point.Point(0, 0)
        >>> PygameGraphics.pos_to_screen(p, 16, 18)
        (0, 0)
        >>> p = point.Point(1, 2)
        >>> PygameGraphics.pos_to_screen(p, 16, 18)
        (16, 36)
        """
        return pos.x * tile_x, pos.y * tile_y

    def tick(self, run_time, delta_time, data):
        # Update screen.
        self.__update_screen(data)

        # Show title and update clock.
        self.__show_title(data)
        self.clock.tick(data.config.fps) # Prevent unnecessary cpu load.

    @staticmethod
    def visible(pos, graphics):
        """ Checks if a position is visible on screen.

        Test:
        >>> from data.world import point
        >>> from data import graphics
        >>> g = graphics.Graphics()
        >>> g.view_offset_x = 1
        >>> g.view_offset_y = 2
        >>> g.view_x = 5
        >>> g.view_y = 10
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
        return graphics.view_offset_x <= pos.x < graphics.view_offset_x + graphics.view_x and \
               graphics.view_offset_y <= pos.y < graphics.view_offset_y + graphics.view_y

    def __calc_view_offset(self, view_offset_x, view_offset_y):
        """ Calculate view offset point. """
        self._view_offset_point = PointFactory.new_point(view_offset_x, view_offset_y)

    def __draw_background(self, data):
        graphics = data.graphics
        for x in range(graphics.view_offset_x, graphics.view_offset_x + graphics.view_x):
            for y in range(graphics.view_offset_y, graphics.view_offset_y + graphics.view_y):
                pos = PointFactory.new_point(x, y)
                self.__draw_pos(pos, data)

    def __draw_entities(self, entities, x, y):
        for entity in entities:
            sprite_img, tile_sprite = self._sprite_loader.get_sprite(entity)
            self.screen.blit(sprite_img, (x, y), tile_sprite)

    def __draw_pos(self, pos, data):
        game = data.game
        graphics = data.graphics

        block = game.region.get_block(pos)
        x, y = self.pos_to_screen(pos -  self._view_offset_point, graphics.tile_x, graphics.tile_y)

        self.__draw_entities(block.get_tiles(), x, y)
        self.__draw_entities(block.get_statics(), x, y)
        self.__draw_entities(block.get_dynamics(), x, y)

        return x, y, graphics.tile_x, graphics.tile_y

    def __show_title(self, data):
        fps = self.clock.get_fps()
        data.fps.append(fps)
        self._fps.append(fps)
        if len(self._fps) > self.MAX_FPS:
            print('Deque to long.')
        text = data.graphics.window_title.format(sum(self._fps) / len(self._fps))
        pygame.display.set_caption(text)

    def __update_screen(self, data):
        graphics = data.graphics

        dirty_rects = []

        # First render tile.
        if graphics.view_updated:
            self.__calc_view_offset(graphics.view_offset_x, graphics.view_offset_y)
            self.__draw_background(data)
        else:
            for pos in data.dirty_pos:
                if self.visible(pos, graphics):
                    rect = self.__draw_pos(pos, data)
                    dirty_rects.append(rect)

        if graphics.view_updated:
            pygame.display.flip()
        else:
            pygame.display.update(dirty_rects)

if __name__ == '__main__':
    print('Executing doctest.')
    import doctest
    doctest.testmod()