import random

from data import id as ID


class DecisionTreeParser:
    """ Executes a decision tree. """

    def parse(self, entity, decision_tree, task_result = None):
        """ Parse the given entity. Returns the next task to execute. """
        node_id = None

        if task_result is not None and entity.last_decision_node:
            node = decision_tree.nodes[entity.last_decision_node]
            if node.next:
                node_id = node.next
            elif task_result and node.success:
                node_id = node.success
            elif not task_result and node.fail:
                node_id = node.fail

        task = None
        while not task:
            if node_id is None:
                node_id = decision_tree.start_nodes[entity.id]
            node = decision_tree.nodes[node_id]
            if node.type == ID.AI_DECISION_NODE_RANDOM:
                node_id = self.__random_node(node)
            elif node.type == ID.AI_DECISION_NODE_TASK:
                task = node.task

        entity.last_decision_node = node_id
        return task

    def __random_node(self, node):
        """ Execute random node. Returns next node id. """
        upper = sum([x.chance for x in node.random])
        dice = random.uniform(0.0, upper)
        chance_from = 0.0
        for random_edge in node.random:
            if chance_from <= dice <= chance_from + random_edge.chance:
                return random_edge.next
            else:
                chance_from += random_edge.chance