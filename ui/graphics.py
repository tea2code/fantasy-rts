import pygame

class PygameGraphics:
    """ Graphical representation of state using pygame.

    Member:
    screen -- The pygame surface which acts as the game screen.
    """

    def __init__(self):
        size = (640, 480)
        self.screen = pygame.display.set_mode(size)

    def tick(self, run_time, delta_time):
        pass