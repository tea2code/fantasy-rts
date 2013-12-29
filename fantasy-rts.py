from data import data
from data import game as gamestate
from data import graphics as graphicsstate
from data import level
from data import tile
from gamemath.vector import Vector2
from general import mainloop
from ui import eventhandler, graphics

class MainLoopImp(mainloop.MainLoop):
    """
    Constants:
    FPS -- Frames per second (int).
    MAX_FRAME_TIME -- Maximum time a frame may take (float).

    Member:
    data -- The data module (data.Data).
    render_modules -- Modules regarding rendering the state (list).
    state_modules -- Modules regarding updating the state (list).
    """

    FPS = 100
    MAX_FRAME_TIME = 0.25

    def __init__(self):
        super().__init__(1.0 / self.FPS, self.MAX_FRAME_TIME)

        # Data.
        size = 100
        game_data = gamestate.Game()
        game_data.level = self.__demo_level(size)
        game_data.tile_x = size
        game_data.tile_y = size

        graphics_data = graphicsstate.Graphics()
        graphics_data.fps = self.FPS
        graphics_data.tile = 16
        graphics_data.view_x = 40
        graphics_data.view_y = 30
        graphics_data.window_title = 'Fantasy-RTS (FPS: {0:.0f})'

        self.data = data.Data()
        self.data.game = game_data
        self.data.graphics = graphics_data

        # State modules.
        self.state_modules = [
            eventhandler.PygameEventHandler()
        ]

        # Render modules.
        self.render_modules = [
            graphics.PygameGraphics(self.data)
        ]

    def render(self, run_time, delta_time):
        for module in self.render_modules:
            module.tick(run_time, delta_time, self.data)

    def update(self, run_time, delta_time):
        for module in self.state_modules:
            module.tick(run_time, delta_time, self.data)

    def __demo_level(self, size):
        lvl = level.Level()
        for x in range(size):
            lvl[Vector2(x, 0)] = tile.WALL
            lvl[Vector2(x, size - 1)] = tile.WALL
        for y in range(size):
            lvl[Vector2(0, y)] = tile.WALL
            lvl[Vector2(size - 1, y)] = tile.WALL
        return lvl

if __name__ == '__main__':
    app = MainLoopImp()
    app.start()