from data import direction, point, tile

def distance(pos1, pos2):
    # Manhattan distance.
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