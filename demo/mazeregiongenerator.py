import random

from data.config import ID
from data.world import block, factory
from data.world.point import  Factory as PointFactory
from world import regiongenerator

class MazeRegionGenerator(regiongenerator.RegionGenerator):
    """ Implementation of the region generator which creates a randomized maze.

    Constants:
    N -- Bitmask for direction north (int).
    S -- Bitmask for direction south (int).
    E -- Bitmask for direction east (int).
    W -- Bitmask for direction west (int).

    Member:
    _map -- The pregenerated map for z-level 0 (dict).
    """

    N, S, E, W = 1, 2, 4, 8

    def __init__(self, data):
        if data.game.size_x % 2 == 0:
            data.game.size_x += 1
        if data.game.size_y % 2 == 0:
            data.game.size_y += 1

        size_x = data.game.size_x
        size_y = data.game.size_y

        size_x_half = int(size_x / 2)
        size_y_half = int(size_y / 2)

        # Initialize everything with wall.
        self._map = {}
        for x in range(size_x):
            for y in range(size_y):
                self._map[PointFactory.new_point(x, y)] = self.__wall_block(data)

        start_x = 1
        start_y = 1
        maze = self.__create_maze(size_x_half, size_y_half)
        for x in range(size_x_half):
            for y in range(size_y_half):
                maze_point = maze[(x, y)]
                mx = 2 * x + start_x
                my = 2 * y + start_y
                self._map[PointFactory.new_point(mx, my)] = self.__grass_block(data)
                if maze_point & self.N:
                    self._map[PointFactory.new_point(mx, my-1)] = self.__grass_block(data)
                if maze_point & self.S:
                    self._map[PointFactory.new_point(mx, my+1)] = self.__grass_block(data)
                if maze_point & self.E:
                    self._map[PointFactory.new_point(mx+1, my)] = self.__grass_block(data)
                if maze_point & self.W:
                    self._map[PointFactory.new_point(mx-1, my)] = self.__grass_block(data)

    def all_blocks(self, z_level):
        return self._map

    def new_block(self, pos):
        return self._map[pos]

    def __create_maze(self, width, height):
        """ Create a maze of given width and height starting at point
        (x, y). Returns maze as a dict (x, y) => Direction """
        dx = { self.E: 1, self.W: -1, self.N: 0, self.S: 0 }
        dy = { self.E: 0, self.W: 0, self.N: -1, self.S: 1 }
        opposite = { self.E: self.W, self.W: self.E, self.N: self.S, self.S: self.N }

        grid = [[0 for _ in range(width)] for _ in range(height)]
        stack = [(0, 0)]

        while stack:
            x, y = stack.pop()

            directions = [self.N, self.S, self.E, self.W]
            random.shuffle(directions)

            for direction in directions:
                nx, ny = x + dx[direction], y + dy[direction]

                in_grid = 0 <= ny < len(grid) and 0 <= nx < len(grid[ny])
                if in_grid and grid[ny][nx] == 0:
                    grid[y][x] |= direction
                    grid[ny][nx] |= opposite[direction]
                    stack.append((nx, ny))

        maze = {}
        y = 0
        for horizontal in grid:
            x = 0
            for vertical in horizontal:
                maze[(x, y)] = vertical
                x += 1
            y += 1
        return maze

    def __grass_block(self, data):
        t = factory.new_tile(data.game.tile_ground, data)
        b = block.Block()
        b.insert_tile(t)
        return b

    def __wall_block(self, data):
        t = factory.new_tile(data.game.tile_wall, data)
        b = block.Block()
        b.insert_tile(t)
        return b