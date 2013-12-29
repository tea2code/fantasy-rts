import pygame

from . import sprite
from data import tile

class PygameSpriteLoader:
    """ Gives access to sprite handling.

    Member:
    _tile_sprite -- Mapping of tile to sprite (dict).
    """

    def __init__(self):
        self._tile_sprite = {
            tile.PLAIN: sprite.PLAIN,
            tile.WALL: sprite.WALL
        }

    def load(self, sprite_path):
        """ Load the sprite image. """
        return pygame.image.load(sprite_path).convert_alpha()

    def sprite_by_tile(self, tile):
        """ Returns the sprite for the given tile. """
        return self._tile_sprite[tile] if tile in self._tile_sprite else sprite.UNKNOWN