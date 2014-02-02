from data import tasklist


class Game:
    """ The game state.

    Member:
    food_plant -- ID of plant for food (string).
    race_player -- ID of race of player (string).
    region -- The game region (data.world.region).
    size_x -- The size of the map in x direction (int).
    size_y -- The size of the map in y direction (int).
    tasks -- The task list (data.tasks).
    tile_ground -- ID of tile of ground (string).
    tile_wall -- ID of tile of wall (string).
    wood_plant -- ID of plant for wood (string).
    """

    def __init__(self):
        self.food_plant = ''
        self.race_player = ''
        self.region = None
        self.size_x = 100
        self.size_y = 100
        self.tasks = tasklist.TaskList()
        self.tile_ground = ''
        self.tile_wall = ''
        self.wood_plant = ''