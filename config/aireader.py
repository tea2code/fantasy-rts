from . import basereader
from data.ai import decision as decision_class
from data.config import ai, ID


class UnknownNodeTypeException(Exception):
    """ Raised if a unknown node type is found in a decision tree. """


class UnknownTaskTypeException(Exception):
    """ Raised if a unknown task type is found. """


class YamlAiReader(basereader.BaseYamlReader):
    """ Yaml reader for ai types.

    Constants:
    CHANCE
    DECISION
    DECISIONS
    DURATION
    ENTITY
    FAIL
    NAME
    NAMESPACE
    NEXT
    RANDOM
    START_NODE
    TASK
    TASKS
    TREE
    TYPE
    VARIANCE_MIN
    VARIANCE_MAX
    SUCCESS
    """

    CHANCE = 'chance'
    DECISION = 'decision'
    DECISIONS = 'decisions'
    DURATION = 'duration'
    ENTITY = 'entity'
    FAIL = 'fail'
    NAME = 'name'
    NAMESPACE = 'namespace'
    NEXT = 'next'
    RANDOM = 'random'
    START_NODE = 'start_node'
    SUCCESS = 'success'
    TASK = 'task'
    TASKS = 'tasks'
    TREE = 'tree'
    TYPE = 'type'
    VARIANCE_MIN = 'variance_min'
    VARIANCE_MAX = 'variance_max'

    def parse(self, root, data):
        """ Parse the task structure. Writes the parsed information into the
        data object. """

        namespace = self.read_req_string(root, self.NAMESPACE)

        if self.has(root, self.DECISIONS):
            self.__decisions(namespace, root, data)
        if self.has(root, self.TASKS):
            self.__tasks(namespace, root, data)

    def __decisions(self, namespace, root, data):
        """ Decision config. """
        decisions = self.read_req_object(root, self.DECISIONS)
        decisions_namespace = [namespace, self.read_req_string(decisions, self.NAMESPACE)]
        for decision in self.read_object(decisions, self.DECISION, []):
            decision_namespace = decisions_namespace + [self.read_req_string(decision, self.NAMESPACE)]

            # Start node.
            entity = self.read_string(decision, self.ENTITY, None)
            start_node = self.read_string(decision, self.START_NODE, None)
            if entity and start_node:
                data.game.decision_tree.start_nodes[entity] = start_node

            # Nodes.
            for node in self.read_object(decision, self.TREE, []):
                name = self.read_req_string(node, self.NAME)
                id = self.namespace_to_id(decision_namespace, name)
                type = self.read_req_string(node, self.TYPE)

                if type == ID.AI_DECISION_NODE_RANDOM:
                    node_obj = decision_class.RandomNode(type)
                    for random in self.read_req_object(node, self.RANDOM):
                        chance = self.read_req_float(random, self.CHANCE)
                        next = self.read_req_string(random, self.NEXT)
                        edge = decision_class.RandomNodeEdge()
                        edge.chance = chance
                        edge.next = next
                        node_obj.random.append(edge)
                elif type == ID.AI_DECISION_NODE_TASK:
                    node_obj = decision_class.TaskNode(type)
                    node_obj.fail = self.read_string(node, self.FAIL, node_obj.fail)
                    node_obj.next = self.read_string(node, self.NEXT, node_obj.next)
                    node_obj.success = self.read_string(node, self.SUCCESS, node_obj.success)
                    node_obj.task = self.read_req_string(node, self.TASK)
                else:
                    raise UnknownNodeTypeException('Type "{0}" is not a known decision tree node type.'.format(type))

                data.game.decision_tree.nodes[id] = node_obj

    def __tasks(self, namespace, root, data):
        """ Task config. """
        tasks = self.read_req_object(root, self.TASKS)
        namespace_list = [namespace, self.read_req_string(tasks, self.NAMESPACE)]

        default_variance_min = self.read_float(tasks, self.VARIANCE_MIN, 0.0)
        default_variance_max = self.read_float(tasks, self.VARIANCE_MAX, 0.0)

        for task in self.read_object(tasks, self.TASK, []):
            name = self.read_req_string(task, self.NAME)
            id = self.namespace_to_id(namespace_list, name)
            type = self.read_req_string(task, self.TYPE)
            variance_min = self.read_float(task, self.VARIANCE_MIN, default_variance_min)
            variance_max = self.read_float(task, self.VARIANCE_MAX, default_variance_max)

            if type == ID.AI_TASK_TYPE_IDLE:
                if self.is_type(task, self.DURATION, float):
                    duration = self.read_req_object(task, self.DURATION)
                else:
                    duration = self.read_req_object(task, self.DURATION)
                task_obj = ai.IdleTask(type, variance_min, variance_max, duration)
            elif type == ID.AI_TASK_TYPE_RANDOM_GOTO:
                task_obj = ai.GoToTask(type, variance_min, variance_max)
            else:
                raise UnknownTaskTypeException('Type "{0}" is not a known task type.'.format(type))

            data.config.ai.tasks[id] = task_obj