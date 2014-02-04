class DecisionTree:
    """ The decision tree for ai.

    Member:
    nodes -- Mapping of node id to node (dict).
    start_node -- Mapping of entity id to start node id (dict).
    """

    def __init__(self):
        self.nodes = {}
        self.start_node = {}

class RandomNode:
    """ A node which makes a decision by throwing a dice.

    Member:
    random -- List of next nodes with chance (list).
    """

    def __init__(self):
        self.random = []

class RandomNodeEdge:
    """ An edge of a random node.

    Member:
    chance -- The chance of this edge (float).
    next -- The id of the next node (string).
    """

    def __init__(self):
        self.chance = 0.0
        self.next = ''

class TaskNode:
    """ A node which executes a task. After executing this node there are
    three possible ways what happens next. If this node has no child the
    decision tree ends here. If it has one child this is executed next. If
    it has a yes and a no child the child corresponding to the result of
    the task is executed.

    Member:
    fail -- Id of the negative result node if two child (string).
    next -- Id of the next node if single child (string).
    success -- Id of the positiv result node if two child (string).
    task -- Id of the task (string).
    """

    def __init__(self):
        self.fail = None
        self.next = None
        self.success = None
        self.task = ''