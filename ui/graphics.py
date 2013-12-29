import pygame

from . import sprite
from data import point
from data import tile

class PygameGraphics:
    """ Graphical representation of state using pygame.

    Member:
    clock -- The pygame clock.
    screen -- The pygame surface which acts as the game screen.
    """

    def __init__(self, data):
        size = (data.graphics.view_x * data.graphics.tile,
                data.graphics.view_y * data.graphics.tile)
        self.screen = pygame.display.set_mode(size)
        self.clock = pygame.time.Clock()
        self.sprite_img = pygame.image.load(data.graphics.sprite).convert_alpha()

        self.__show_title(data.graphics.window_title)
        self.__draw_background(data)

    def tick(self, run_time, delta_time, data):
        # Show title and update clock.
        self.__show_title(data.graphics.window_title)
        self.clock.tick(data.graphics.fps) # Prevent unnecessary cpu load.

        # Update screen.
        self.__update_screen(data)

    def __draw_background(self, data):
        for x in range(data.graphics.view_x):
            for y in range(data.graphics.view_y):
                pos = point.Point(x, y)
                self.__draw_pos(pos, data)
        pygame.display.flip()

    def __draw_pos(self, pos, data):
        x, y = self.__pos_to_screen(pos, data.graphics.tile)
        rect = (x, y, data.graphics.tile, data.graphics.tile)
        pos = pos + point.Point(data.graphics.view_offset_x, data.graphics.view_offset_y)
        level_tile = data.game.level[pos] if pos in data.game.level else data.game.level.default_tile
        if level_tile is tile.WALL:
            tile_sprite = sprite.WALL
        elif level_tile is tile.PLAIN:
            tile_sprite = sprite.PLAIN
        else:
            # Unknown tile type.
            tile_sprite = sprite.UNKNOWN
        self.screen.blit(self.sprite_img, (x, y), tile_sprite)
        return rect

    def __pos_to_screen(self, pos, tile):
        return int(pos.x * tile), int(pos.y * tile)

    def __show_title(self, window_title):
        fps = self.clock.get_fps()
        text = window_title.format(fps)
        pygame.display.set_caption(text)

    def __update_screen(self, data):
        if data.graphics.view_updated:
            self.__draw_background(data)

        if data.graphics.view_updated:
            pygame.display.flip()
            data.graphics.view_updated = False