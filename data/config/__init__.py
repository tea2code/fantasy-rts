class ID:
    """ ID constants.

    Constants with _ as prefix are no IDs but used for validation...
    """

    ACTION_SCROLL_NORTH = 'action.scroll_north'
    ACTION_SCROLL_SOUTH = 'action.scroll_south'
    ACTION_SCROLL_WEST = 'action.scroll_west'
    ACTION_SCROLL_EAST = 'action.scroll_east'
    ACTION_SCROLL_UP = 'action.scroll_up'
    ACTION_SCROLL_DOWN = 'action.scroll_down'
    _ACTION_SCROLL = [ACTION_SCROLL_DOWN, ACTION_SCROLL_EAST, ACTION_SCROLL_NORTH,
                      ACTION_SCROLL_SOUTH, ACTION_SCROLL_UP, ACTION_SCROLL_WEST]

    ENTITY_ATTRIBUTE_MOVING_WALK = 'entity.attribute.moving.walk'
    _ENTITY_ATTRIBUTE_MOVING = [ENTITY_ATTRIBUTE_MOVING_WALK]

    ENTITY_DYNAMIC_DWARF = 'entity.dynamic.dwarf'
    ENTITY_STATIC_BERRY_SHRUB = 'entity.static.berry-shrub'
    ENTITY_STATIC_TREE = 'entity.static.tree'
    ENTITY_TILE_GRASS = 'entity.tile.grass'
    ENTITY_TILE_WALL = 'entity.tile.wall'

    STATE_DIRECTION_NORTH = 'north'
    STATE_DIRECTION_SOUTH = 'south'
    STATE_DIRECTION_EAST = 'east'
    STATE_DIRECTION_WEST = 'west'
    STATE_DIRECTION_UP = 'up'
    STATE_DIRECTION_DOWN = 'down'
    STATE_DIRECTION_STOP = 'stop'