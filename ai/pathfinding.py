from data import direction, point, tile

def distance(pos1, pos2):
    """ Calculates the Manhattan distance between two points.

    Test:
    >>> p1 = point.Point(5, 5)
    >>> p2 = point.Point(1, 2)
    >>> d = distance(p1, p2)
    >>> '{0:.2f}'.format(d)
    '7.00'
    """
    return abs(pos1.x - pos2.x) + abs(pos1.y - pos2.y)

class Node:
    def __init__(self, pos, goal):
        self.goal = goal
        self.pos = pos
        self.parent = None
        self._score = None

    def score(self):
        if self._score is None:
            self._score = distance(self.goal, self.pos)
        return self._score

    def __eq__(self, other):
        return self.pos == other.pos

    def __hash__(self):
        return self.pos.__hash__()

class AStar:
    """ Path finding using A*. """

    def shortest_path(self, level, start, goal):
        """ Calculates the shortest path using the A* algorithm.

        Test:
        s = start
        g = goal
        W = Wall
        [s    ]
        [  W  ]
        [  g  ]
        Result: Down, Down, Right
        >>> start = point.Point(0, 0)
        >>> goal = point.Point(1, 2)
        >>> wall = point.Point(1, 1)
        >>> level = {wall: tile.WALL}
        >>> a_star = AStar()
        >>> path = a_star.shortest_path(level, start, goal)
        >>> path = [x.int_tuple2() for x in path]
        >>> print(path)
        [(0, 1), (0, 1), (1, 0)]
        """
        path = self.__find_path(level, start, goal)
        result = []
        length = len(path)
        for index, node in enumerate(path):
            if index is length - 1:
                break
            x = path[index + 1].pos.x - node.pos.x
            y = path[index + 1].pos.y - node.pos.y
            result.append(point.Point(x, y))
        return result

    def __find_path(self, level, start, goal):
        current = Node(start, goal)
        end = Node(goal, goal)

        open = set()
        closed = set()

        open.add(current)
        while open:
            current = min(open, key=lambda x: x.score())
            if current == end:
                return self.__retrace_path(current)

            open.remove(current)
            closed.add(current)

            # TODO Totally buggy. See border of map. Might be no problem but better use another map format.
            neighbors = [Node(current.pos + direction.UP, goal),
                         Node(current.pos + direction.DOWN, goal),
                         Node(current.pos + direction.LEFT, goal),
                         Node(current.pos + direction.RIGHT, goal)]

            for neighbor in neighbors:
                if neighbor.pos in level and level[neighbor.pos] is tile.WALL:
                    continue

                if neighbor not in closed:
                    if neighbor not in open:
                        open.add(neighbor)
                    neighbor.parent = current
        return []

    def __retrace_path(self, c):
        path = [c]
        while c.parent is not None:
            c = c.parent
            path.append(c)
        path.reverse()
        return path

if __name__ == '__main__':
    print('Executing doctest.')
    import doctest
    doctest.testmod()