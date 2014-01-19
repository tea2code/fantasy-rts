import heapq

class EuclideanDistance:
    """ Calculates the euclidean distance of two points. """

    def distance(self, pos1, pos2):
        """ Calculate the distance.

        Test:
        >>> from data.world import point
        >>> p1 = point.Point(5, 5, 1)
        >>> p2 = point.Point(1, 2, 0)
        >>> ed = EuclideanDistance()
        >>> d = ed.distance(p1, p2)
        >>> '{0:.2f}'.format(d)
        '5.10'
        """
        return (pos1 - pos2).length()

class ManhattanDistance:
    """ Calculates the manhattan distance of two points. """

    def distance(self, pos1, pos2):
        """ Calculate the distance.

        Test:
        >>> from data.world import point
        >>> p1 = point.Point(5, 5, 1)
        >>> p2 = point.Point(1, 2, 0)
        >>> md = ManhattanDistance()
        >>> d = md.distance(p1, p2)
        >>> '{0:.2f}'.format(d)
        '8.00'
        """
        return abs(pos1.x - pos2.x) + \
               abs(pos1.y - pos2.y) + \
               abs(pos1.z - pos2.z)

class Node:
    def __init__(self, pos):
        self.pos = pos
        self.parent = None
        self.score = 0

    def __eq__(self, other):
        return self.pos == other.pos

    def __hash__(self):
        return self.pos.__hash__()

    def __lt__(self, other):
        return True

class AStar:
    """ Path finding using A*.

    Member:
    heuristic -- Heuristic which calculates the distance of two points.
    """

    def __init__(self, heuristic):
        self.heuristic = heuristic

    def shortest_path(self, start, goal, blocked, region):
        """ Calculates the shortest path using the A* algorithm. Returns None
        if no path was found.

        Test:
        s = start
        g = goal
        W = Wall
        [s    ]
        [  W  ]
        [  g  ]
        Result: Down, Down, Right
        >>> from data.world import tile
        >>> t = tile.Tile('id')
        >>> t.blocking = ['block']
        >>> from data.world import point
        >>> wall = point.Point(1, 1)
        >>> start = point.Point(0, 0)
        >>> goal = point.Point(1, 2)
        >>> from test import regiongenerator
        >>> rg = regiongenerator.AllGrassRegionGenerator(3, 3)
        >>> from data.world import region
        >>> r = region.Region(rg, 3, 3)
        >>> r.set_pos(t, wall)
        >>> md = ManhattanDistance()
        >>> a_star = AStar(md)
        >>> path = a_star.shortest_path(start, goal, ['block'], r)
        >>> path = [x.tuple2() for x in path]
        >>> print(path)
        [(0, 1), (0, 2), (1, 2)]
        """
        path = self.__find_path(start, goal, blocked, region)
        if path:
            return [node.pos for node in path][1:]
        else:
            return path

    def __find_path(self, start, goal, blocked, region):
        current = Node(start)
        current.score = self.__distance(start, goal)
        end = Node(goal)

        openSet = set()
        openHeap = []
        closedSet = set()

        openSet.add(current)
        openHeap.append((0, current))
        while openSet:
            current = heapq.heappop(openHeap)[1]
            if current == end:
                return self.__retrace_path(current)

            openSet.remove(current)
            closedSet.add(current)

            neighbor_pos = region.free_neighbors(current.pos, blocked)
            neighbors = [Node(pos) for pos in neighbor_pos]

            for neighbor in neighbors:
                if neighbor not in closedSet:
                    neighbor.score = self.__distance(neighbor.pos, goal)
                    if neighbor not in openSet:
                        openSet.add(neighbor)
                        heapq.heappush(openHeap, (neighbor.score, neighbor))
                    neighbor.parent = current

        return None

    def __distance(self, start, goal):
        """ Calculates the distance of the two points. """
        return self.heuristic.distance(start, goal)

    def __retrace_path(self, node):
        """ Retrace the path of the given node. """
        path = [node]
        while node.parent is not None:
            node = node.parent
            path.append(node)
        path.reverse()
        return path

if __name__ == '__main__':
    print('Executing doctest.')
    import doctest
    doctest.testmod()