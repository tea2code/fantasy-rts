from data.config import ID

class ValidatorError(Exception):
    """ Thrown if a data violation is found. """

class Validator:
    """ Validates the current configuration. This includes plausibility checks
    and the usage of IDs. """

    def validate(self, data):
        """ Validate the given data object. Throws an exception with detailed
        information in case of a data violation. """
        self.__validate_data(data)
        self.__validate_config(data.config)
        self.__validate_game(data.game)
        self.__validate_graphics(data.graphics)

    def __validate_config(self, config):
        """ Validate configuration part. """
        if config.fps <= 0:
            raise ValidatorError('Config.fps must be bigger than 0.')
        if config.max_frame_time < 1.0 / config.fps:
            raise ValidatorError('Config.max_frame_time must be bigger than actual frame time (1 / Config.fps).')
        if config.num_fps_avg <= 0:
            raise ValidatorError('Config.num_fps_avg must be bigger than 0.')
        if config.scroll_width_x <= 0 or config.scroll_width_y <= 0:
            raise ValidatorError('Config.scroll_width_x and Config.scroll_width_y must be bigger than 0.')
        if '{0}' not in config.state_id:
            raise ValidatorError('Config.state_id must contain "{0}".')

        # Keys
        keys = config.keys
        for key, value in keys.items():
            if key not in ID._ACTION_SCROLL:
                raise ValidatorError('Config.keys contains unknown action "{0}".'.format(key))

        # Resources
        resources = config.resources
        for key, value in resources.resources.items():
            if value.type not in resources.types:
                raise ValidatorError('Resource "{0}" has unknown type "{1}".'.format(key, value.type))
            if value.value < 0.0:
                raise ValidatorError('Value of resource "{0}" may not be negative.'.format(key))

        # Entity
        entity = config.entity

        # Dynamic
        for key, value in entity.dynamics.items():
            for blocked in value.blocked:
                if blocked.type not in entity.attributes:
                    raise ValidatorError('Dynamic entity "{0}" has unknown blocked type "{1}".'.format(key, blocked.type))
            for moving in value.moving:
                if moving.type not in ID._ENTITY_ATTRIBUTE_MOVING:
                    raise ValidatorError('Dynamic entity "{0}" has unknown moving type "{1}".'.format(key, moving.type))
                if moving.speed < 0.0:
                    raise ValidatorError('Speed of moving type "{0}" of dynamic entity "{1}" may not be negative.'.format(moving.type, key))

        # Static
        for key, value in entity.statics.items():
            for blocked in value.blocked:
                if blocked.type not in entity.attributes:
                    raise ValidatorError('Static entity "{0}" has unknown blocked type "{1}".'.format(key, blocked.type))
            for blocking in value.blocking:
                if blocking.type not in entity.attributes:
                    raise ValidatorError('Static entity "{0}" has unknown blocking type "{1}".'.format(key, blocking.type))
            for resource in value.resources:
                if resource.type not in resources.resources:
                    raise ValidatorError('Static entity "{0}" has unknown resource type "{1}".'.format(key, resource.type))
                if resource.chance < 0.0:
                    raise ValidatorError('Chance of resource type "{0}" of static entity "{1}" may not be negative.'.format(resource.type, key))

        # Tiles
        for key, value in entity.tiles.items():
            for blocking in value.blocking:
                if blocking.type not in entity.attributes:
                    raise ValidatorError('Tile entity "{0}" has unknown blocking type "{1}".'.format(key, blocking.type))

        # Style
        style = config.style
        if not style.default_mapping:
            raise ValidatorError('Style.default_mapping may not be empty.')

        # Images
        for key, value in style.images.items():
            if not value.path:
                raise ValidatorError('Image "{0}" must not have an empty path.'.format(key))

        # Sprites
        for key, value in style.sprites.items():
            if not isinstance(value, list):
                value = [value]
            for v in value:
                if v.image not in style.images:
                    raise ValidatorError('Sprite "{0}" has unknown image "{1}".'.format(key, v.image))
                if v.x < 0 or v.y < 0:
                    raise ValidatorError('Coordinates of sprite "{0}" may not be negative.'.format(key))

        # Mappings
        for map, to in style.mappings.items():
            if to not in style.sprites:
                raise ValidatorError('Map ID "{0}" has unknown to ID "{1}".'.format(map, to))

    def __validate_data(self, data):
        """ Validate data part. """
        pass

    def __validate_game(self, game):
        """ Validate game part. """
        if game.size_x <= 0 or game.size_y <= 0:
            raise ValidatorError('Game.size_x and Game.size_y must be bigger than 0.')

    def __validate_graphics(self, graphics):
        """ Validate graphics part. """
        if graphics.tile_x <= 0 or graphics.tile_y <= 0:
            raise ValidatorError('Graphics.tile_x and Graphics.tile_y must be bigger than 0.')
        if graphics.view_x <= 0 or graphics.view_y <= 0:
            raise ValidatorError('Graphics.view_x and Graphics.view_y must be bigger than 0.')