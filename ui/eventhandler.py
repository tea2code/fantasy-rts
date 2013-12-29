import pygame
import sys

class PygameEventHandler:
    """ Handles pygame events. """

    def tick(self, run_time, delta_time, data):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                sys.exit()