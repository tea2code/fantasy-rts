import pygame

from . import sprite
from data import direction
from data import tile

class PygameSpriteLoader:
    """ Gives access to sprite handling.

    Member:
    _dir_sprite -- Mapping of direction to sprite (dict).
    _tile_sprite -- Mapping of tile to sprite (dict).
    """

    def __init__(self):
        self._dir_sprite = {
            direction.UP: sprite.CREATURE_UP,
            direction.DOWN: sprite.CREATURE_DOWN,
            direction.LEFT: sprite.CREATURE_LEFT,
            direction.RIGHT: sprite.CREATURE_RIGHT
        }
        self._tile_sprite = {
            tile.PLAIN: sprite.PLAIN,
            tile.WALL: sprite.WALL
        }

    def load(self, sprite_path):
        """ Load the sprite image. """
        return pygame.image.load(sprite_path).convert_alpha()

    def creature_sprite_by_dir(self, direction):
        """ Returns the creature sprite for the given direction. """
        return self._dir_sprite[direction] if direction in self._dir_sprite else sprite.UNKNOWN

    def sprite_by_tile(self, tile):
        """ Returns the sprite for the given tile. """
        return self._tile_sprite[tile] if tile in self._tile_sprite else sprite.UNKNOWN