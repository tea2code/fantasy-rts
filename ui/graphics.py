import pygame

class PygameGraphics:
    """ Graphical representation of state using pygame.

    Member:
    clock -- The pygame clock.
    screen -- The pygame surface which acts as the game screen.
    """

    def __init__(self, data):
        size = (data.graphics.view_x * data.game.tile,
                data.graphics.view_y * data.game.tile)
        self.screen = pygame.display.set_mode(size)
        self.clock = pygame.time.Clock()

        self.__show_title(data.graphics.window_title)

    def tick(self, run_time, delta_time, data):
        # Show title and update clock.
        self.__show_title(data.graphics.window_title)
        self.clock.tick(data.graphics.fps) # Prevent unnecessary cpu load.

        # Update screen.
        self.__update_screen(data)

    def __show_title(self, window_title):
        fps = self.clock.get_fps()
        text = window_title.format(fps)
        pygame.display.set_caption(text)

    def __update_screen(self, data):
        pass