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

    ENTITY_ATTRIBUTE_MOVING_WALK = 'entity.attribute.moving.walk'
    _ENTITY_ATTRIBUTE_MOVING = [ENTITY_ATTRIBUTE_MOVING_WALK]

    STATE_DIRECTION_NORTH = 'north'
    STATE_DIRECTION_SOUTH = 'south'
    STATE_DIRECTION_EAST = 'east'
    STATE_DIRECTION_WEST = 'west'
    STATE_DIRECTION_UP = 'up'
    STATE_DIRECTION_DOWN = 'down'
    STATE_DIRECTION_STOP = 'stop'

    TASK_PARAMETER_TIME = 'task.parameter.time'
    _TASK_PARAMETER = [TASK_PARAMETER_TIME]

    TASK_TYPE_IDLE = 'task.type.idle'
    TASK_TYPE_RANDOM_GOTO = 'task.type.randomgoto'
    _TASK_TYPE = [TASK_TYPE_IDLE, TASK_TYPE_RANDOM_GOTO]

    TASK_IDLE = 'ai.task.idle'
    TASK_GOTO = 'ai.task.randomgoto'