""" ID constants.

Constants with _ as prefix are no IDs but used for validation...
"""

# Actions.
ACTION_CURSOR_NORTH = 'action.cursor_north'
ACTION_CURSOR_SOUTH = 'action.cursor_south'
ACTION_CURSOR_WEST = 'action.cursor_west'
ACTION_CURSOR_EAST = 'action.cursor_east'
ACTION_SCROLL_NORTH = 'action.scroll_north'
ACTION_SCROLL_SOUTH = 'action.scroll_south'
ACTION_SCROLL_WEST = 'action.scroll_west'
ACTION_SCROLL_EAST = 'action.scroll_east'
ACTION_SCROLL_UP = 'action.scroll_up'
ACTION_SCROLL_DOWN = 'action.scroll_down'
_ACTION_SCROLL = [ACTION_SCROLL_DOWN, ACTION_SCROLL_EAST, ACTION_SCROLL_NORTH,
                  ACTION_SCROLL_SOUTH, ACTION_SCROLL_UP, ACTION_SCROLL_WEST,
                  ACTION_CURSOR_EAST, ACTION_CURSOR_NORTH, ACTION_CURSOR_SOUTH,
                  ACTION_CURSOR_WEST]

# Decision tree nodes.
AI_DECISION_NODE_RANDOM = 'ai.decision.node.random'
AI_DECISION_NODE_TASK = 'ai.decision.node.task'
AI_DECISION_NODE_PIPELINE_START = 'ai.decision.node.pipeline.start'
AI_DECISION_NODE_PIPELINE_STOP = 'ai.decision.node.pipeline.stop'
_AI_DECISION_NODE = [AI_DECISION_NODE_TASK, AI_DECISION_NODE_RANDOM,
                     AI_DECISION_NODE_PIPELINE_START, AI_DECISION_NODE_PIPELINE_STOP]

# Task types.
AI_TASK_TYPE_IDLE = 'ai.task.type.idle'
AI_TASK_TYPE_GOTO = 'ai.task.type.goto'
AI_TASK_TYPE_FIND_RESOURCE = 'ai.task.type.find.resource'
AI_TASK_TYPE_FIND_ENTITY = 'ai.task.type.find.entity'
AI_TASK_TYPE_DEMO_RANDOMPOINT = 'ai.task.type.demo.randompoint'
AI_TASK_TYPE_HARVEST = 'ai.task.type.harvest'
AI_TASK_TYPE_DROP = 'ai.task.type.drop'
AI_TASK_TYPE_RELEASE_RESOURCE = 'ai.task.type.release.resource'
AI_TASK_TYPE_PIPELINE_VALUE = 'ai.task.type.pipeline.value'
_AI_TASK_TYPE = [AI_TASK_TYPE_IDLE, AI_TASK_TYPE_GOTO, AI_TASK_TYPE_DEMO_RANDOMPOINT,
                 AI_TASK_TYPE_FIND_RESOURCE, AI_TASK_TYPE_HARVEST, AI_TASK_TYPE_FIND_ENTITY,
                 AI_TASK_TYPE_DROP, AI_TASK_TYPE_RELEASE_RESOURCE, AI_TASK_TYPE_PIPELINE_VALUE]

# Entity attributes.
ENTITY_ATTRIBUTE_MOVING_WALK = 'entity.attribute.moving.walk'
_ENTITY_ATTRIBUTE_MOVING = [ENTITY_ATTRIBUTE_MOVING_WALK]

# Entity states.
STATE_DIRECTION_NORTH = 'north'
STATE_DIRECTION_SOUTH = 'south'
STATE_DIRECTION_EAST = 'east'
STATE_DIRECTION_WEST = 'west'
STATE_DIRECTION_UP = 'up'
STATE_DIRECTION_DOWN = 'down'
STATE_DIRECTION_STOP = 'stop'