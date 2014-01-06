import pygame

from data import direction
from data import tile

class PygameSpriteLoader:
    """ Gives access to sprite handling.

    Member:
    _sprite_images -- Mapping of image sprites to ids (dict).
    _style -- The style object (data.config.style).
    """

    def __init__(self, data):
        self._style = data.config.style
        self._sprite_images = {}
        for id in self._style.images:
            dir = data.config.config_dir + self._style.images[id]
            self._sprite_images[id] = pygame.image.load(dir).convert_alpha()

    def get_sprite(self, id):
        """ Returns the sprite image and the sprite coordinates for the given
        entity id. """
        sprite_id = self._style.mappings[id] if id in self._style.mappings else self._style.default_mapping
        sprite = self._style.sprites[sprite_id]
        image = self._sprite_images[sprite.image]
        return image, (sprite.x, sprite.y, sprite.width, sprite.height)

    def sprite_by_tile(self, t):
        """ Only for compatibility. Remove later. """
        if t is tile.PLAIN:
            id = 'tile.plain'
        else:
            id = 'tile.wall'
        return self.get_sprite(id)

    def creature_sprite_by_dir(self, dir):
        """ Only for compatibility. Remove later. """
        if dir is direction.UP:
            id = 'entity.creature-up'
        elif dir is direction.LEFT:
            id = 'entity.creature-left'
        elif dir is direction.DOWN:
            id = 'entity.creature-down'
        else:
            id = 'entity.creature-right'
        return self.get_sprite(id)