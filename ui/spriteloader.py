import pygame

from data.world.entity import movable


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

    def get_sprite(self, entity):
        """ Returns the sprite image and the sprite coordinates for the given
        entity. """
        id = entity.id
        if isinstance(entity, movable.Walking):
            if entity.direction is movable.Direction.NORTH:
                id += '-north'
            elif entity.direction is movable.Direction.SOUTH:
                id += '-south'
            elif entity.direction is movable.Direction.WEST:
                id += '-west'
            else:
                id += '-east'
        sprite_id = self._style.mappings[id] if id in self._style.mappings else self._style.default_mapping
        sprite = self._style.sprites[sprite_id]
        image = self._sprite_images[sprite.image]
        return image, (sprite.x, sprite.y, sprite.width, sprite.height)