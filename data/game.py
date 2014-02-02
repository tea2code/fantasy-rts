from data.config import tasklist


class Game:
    """ The game state.

    Member:
    creature -- List of creatures (list).
    region -- The game region (data.world.region).
    size_x -- The size of the map in x direction (int).
    size_y -- The size of the map in y direction (int).
    tasks -- The task list (data.tasks).
    """

    def __init__(self):
        self.region = None
        self.size_x = 100
        self.size_y = 100
        self.tasks = tasklist.TaskList()