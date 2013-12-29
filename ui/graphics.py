import pygame

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

        self.__show_title(data.graphics.window_title)

    def tick(self, run_time, delta_time, data):
        # Show title and update clock.
        self.__show_title(data.graphics.window_title)
        self.clock.tick(data.graphics.fps) # Prevent unnecessary cpu load.

        # Update screen.
        self.__update_screen(data)

    def __draw_background(self, data):
        for x in range(data.graphics.view_x):
            for y in range(data.graphics.view_y):
                pos = Point2(x, y)
                self.__draw_pos(pos, data)
        pygame.display.flip()

    def __draw_pos(self, pos, data):
        x, y = self.__pos_to_screen(pos, data)
        rect = (x, y, data.tile, data.tile)
        pos = pos + Point2(data.view_offset_x, data.view_offset_y)
        tile = data.map[pos] if pos in data.map else data.map.default_tile
        if tile is tile.WALL:
            sprite = Sprite.WALL
        elif tile is tile.PLAIN:
            sprite = Sprite.PLAIN
        else:
            # Unknown tile type.
            sprite = Sprite.UNKNOWN
        self.screen.blit(self.sprite_img, (x, y), sprite)
        return rect

    def __pos_to_screen(self, pos, data):
        return int(pos.x * data.game.tile), int(pos.y * data.tile)

    def __show_title(self, window_title):
        fps = self.clock.get_fps()
        text = window_title.format(fps)
        pygame.display.set_caption(text)

    def __update_screen(self, data):
        pass