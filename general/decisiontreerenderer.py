import os
import matplotlib.pyplot as plt
import networkx as nx

from data import id as ID


class DecisionTreeRenderer:
    """ Renders a decision tree for visualization.

    Constants:
    LABEL_FAIL -- Edge label for failure (string).
    LABEL_SUCCESS -- Edge label for success (string).
    NODE_SIZE -- Size of a node (int).
    TYPE_RANDOM -- Type of random node (string).
    TYPE_START -- Type of start node (string).
    TYPE_TASK -- Type of task node (string).

    Member:
    directory -- The directory of the resulting graphs (string).
    file_template -- The template for file names (string).
    """

    LABEL_FAIL = 'fail'
    LABEL_SUCCESS = 'success'
    NODE_SIZE = 2000
    TYPE_RANDOM = 'R'
    TYPE_START = 'S'
    TYPE_TASK = 'T'
    TYPE_PIPELINE_START = 'TPS'
    TYPE_PIPELINE_STOP = 'TPS'
    ID_TYPE = {
        ID.AI_DECISION_NODE_TASK: TYPE_TASK,
        ID.AI_DECISION_NODE_RANDOM: TYPE_RANDOM,
        ID.AI_DECISION_NODE_PIPELINE_START: TYPE_PIPELINE_START,
        ID.AI_DECISION_NODE_PIPELINE_STOP: TYPE_PIPELINE_STOP
    }

    def __init__(self, directory, file_template):
        self.directory = directory
        self.file_template = file_template

        if not os.path.exists(directory):
            os.makedirs(directory)

    def render(self, start_nodes, nodes):
        """ Renders given start_nodes and nodes. """
        for entity, start_node in start_nodes.items():
            self.__render_tree(entity, start_node, nodes)

    def __id_to_name(self, type, id):
        """ Converts id to node name. """
        return type + ':' + id.split('.')[-1]

    def __render_tree(self, entity, start_node, nodes):
        """ Render a single tree. """
        # Build graph.
        g = nx.DiGraph()
        edge_labels = {}

        entity_name = self.__id_to_name(self.TYPE_START, entity)
        start_node_name = self.__id_to_name(self.ID_TYPE[nodes[start_node].type], start_node)
        g.add_edge(entity_name, start_node_name)

        for id, node in nodes.items():
            name = self.__id_to_name(self.ID_TYPE[nodes[id].type], id)
            if node.type == ID.AI_DECISION_NODE_RANDOM:
                for random in node.random:
                    random_name = self.__id_to_name(self.ID_TYPE[nodes[random.next].type], random.next)
                    g.add_edge(name, random_name)
                    edge_labels[(name, random_name)] = str(random.chance)
            elif node.type == ID.AI_DECISION_NODE_TASK:
                if node.next is not None:
                    next_name = self.__id_to_name(self.ID_TYPE[nodes[node.next].type], node.next)
                    g.add_edge(name, next_name)
                elif node.success is not None:
                    success_name = self.__id_to_name(self.ID_TYPE[nodes[node.success].type], node.success)
                    g.add_edge(name, success_name)
                    edge_labels[(name, success_name)] = self.LABEL_SUCCESS
                elif node.fail is not None:
                    fail_name = self.__id_to_name(self.ID_TYPE[nodes[node.fail].type], node.fail)
                    g.add_edge(name, fail_name)
                    edge_labels[(name, fail_name)] = self.LABEL_FAIL
            elif node.type == ID.AI_DECISION_NODE_PIPELINE_START:
                next_name = self.__id_to_name(self.ID_TYPE[nodes[node.next].type], node.next)
                g.add_edge(name, next_name)
            elif node.type == ID.AI_DECISION_NODE_PIPELINE_STOP:
                if node.next is not None:
                    next_name = self.__id_to_name(self.ID_TYPE[nodes[node.next].type], node.next)
                    g.add_edge(name, next_name)

        # Setup rendering.
        pos = nx.spectral_layout(g)
        nx.draw_networkx_nodes(g, pos, node_size=self.NODE_SIZE)
        nx.draw_networkx_edges(g, pos)
        nx.draw_networkx_labels(g, pos)
        nx.draw_networkx_edge_labels(g, pos, edge_labels=edge_labels)

        # Save graph.
        file = self.directory + self.file_template.format(entity.split('.')[-1])
        plt.axis('off')
        plt.savefig(file)