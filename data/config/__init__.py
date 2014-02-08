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

    AI_DECISION_NODE_RANDOM = 'ai.decision.node.random'
    AI_DECISION_NODE_TASK = 'ai.decision.node.task'
    _AI_DECISION_NODE = [AI_DECISION_NODE_TASK, AI_DECISION_NODE_RANDOM]

    AI_TASK_PARAMETER_TIME = 'ai.task.parameter.time'

    AI_TASK_TYPE_IDLE = 'ai.task.type.idle'
    AI_TASK_TYPE_RANDOM_GOTO = 'ai.task.type.randomgoto'
    _AI_TASK_TYPE = [AI_TASK_TYPE_IDLE, AI_TASK_TYPE_RANDOM_GOTO]

    ENTITY_ATTRIBUTE_MOVING_WALK = 'entity.attribute.moving.walk'
    _ENTITY_ATTRIBUTE_MOVING = [ENTITY_ATTRIBUTE_MOVING_WALK]

    STATE_DIRECTION_NORTH = 'north'
    STATE_DIRECTION_SOUTH = 'south'
    STATE_DIRECTION_EAST = 'east'
    STATE_DIRECTION_WEST = 'west'
    STATE_DIRECTION_UP = 'up'
    STATE_DIRECTION_DOWN = 'down'
    STATE_DIRECTION_STOP = 'stop'