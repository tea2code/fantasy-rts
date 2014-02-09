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
        self.__validate_game(data.game, data.config.entity, data.config.ai.tasks)
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

        # Ai
        ai = config.ai

        # Tasks
        tasks = ai.tasks
        for key, value in tasks.items():
            if value.type not in ID._AI_TASK_TYPE:
                raise ValidatorError('Task "{0}" has unknown type "{1}".'.format(key, value.type))
            if value.variance_max < value.variance_min:
                raise ValidatorError('Task "{0}" variance max must not be smaller than variance min.'.format(key))
            if value.type == ID.AI_TASK_TYPE_IDLE:
                if isinstance(value.duration, float) and value.duration < 0:
                    raise ValidatorError('Duration of task "{0}" may not be negative.'.format(key))
                elif isinstance(value.duration, list) and not value.duration:
                    raise ValidatorError('Duration list of task "{0}" may not be empty.'.format(key))

    def __validate_data(self, data):
        """ Validate data part. """
        pass

    def __validate_game(self, game, entity, tasks):
        """ Validate game part. """
        if not game.food_plant:
                raise ValidatorError('Game.food_plant must not be empty.')
        if not game.race_player:
                raise ValidatorError('Game.race_player must not be empty.')
        if game.size_x <= 0 or game.size_y <= 0:
            raise ValidatorError('Game.size_x and Game.size_y must be bigger than 0.')
        if not game.tile_ground:
                raise ValidatorError('Game.tile_ground must not be empty.')
        if not game.tile_wall:
                raise ValidatorError('Game.tile_wall must not be empty.')
        if not game.wood_plant:
                raise ValidatorError('Game.wood_plant must not be empty.')

        # Decisions
        decision_tree = game.decision_tree
        for key, value in decision_tree.start_nodes.items():
            if key not in entity.dynamics:
                raise ValidatorError('DecisionTree.start_nodes has a unknown entity "{0}".'.format(key))
            if value not in decision_tree.nodes:
                raise ValidatorError('Start node "{0}" for entity "{1}" is unknown.'.format(value, key))
        for key, value in decision_tree.nodes.items():
            if value.type not in ID._AI_DECISION_NODE:
                raise ValidatorError('Node "{0}" has unknown node type "{1}".'.format(key, value.type))
            if value.type == ID.AI_DECISION_NODE_RANDOM:
                for random in value.random:
                    if random.chance < 0.0:
                        raise ValidatorError('Chance of node "{0}" may not be negative.'.format(key))
                    if random.next not in decision_tree.nodes:
                        raise ValidatorError('Node "{0}" has a unknown child node "{1}".'.format(key, random.next))
            elif value.type == ID.AI_DECISION_NODE_TASK:
                if value.task not in tasks:
                    raise ValidatorError('Task "{0}" of node "{1}" is unknown.'.format(value.task, key))
                if value.fail and value.fail not in decision_tree.nodes:
                    raise ValidatorError('Node "{0}" has a unknown child node "{1}".'.format(key, value.fail))
                if value.next and value.next not in decision_tree.nodes:
                    raise ValidatorError('Node "{0}" has a unknown child node "{1}".'.format(key, value.next))
                if value.success and value.success not in decision_tree.nodes:
                    raise ValidatorError('Node "{0}" has a unknown child node "{1}".'.format(key, value.success))
            else:
                raise ValidatorError('Missing validation of node type "{0}".'.format(value.type))

    def __validate_graphics(self, graphics):
        """ Validate graphics part. """
        if graphics.tile_x <= 0 or graphics.tile_y <= 0:
            raise ValidatorError('Graphics.tile_x and Graphics.tile_y must be bigger than 0.')
        if graphics.view_x <= 0 or graphics.view_y <= 0:
            raise ValidatorError('Graphics.view_x and Graphics.view_y must be bigger than 0.')