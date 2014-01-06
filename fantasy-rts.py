import config

from ai import director
from data import configuration
from data import data
from data import game as gamestate
from data import graphics as graphicsstate
from data.config import style
from general import cleaner
from general import demo
from general import mainloop
from ui import eventhandler, graphics

class MainLoopImp(mainloop.MainLoop):
    """
    Constants:
    CONFIG_DIR -- Directory of the configuration (string).

    Member:
    data -- The data module (data.Data).
    render_modules -- Modules regarding rendering the state (list).
    state_modules -- Modules regarding updating the state (list).
    """

    CONFIG_DIR = 'mod/'

    def __init__(self):
        # Data.
        self.data = data.Data()
        self.data.config.config_dir = self.CONFIG_DIR

        # Load configuration.
        config.load_config(self.data, self.CONFIG_DIR)

        # Demo mode.
        demo_loader = demo.Demo(self.data)
        demo_loader.load(self.data.game.size_x, self.data.game.size_y)

        # State modules.
        self.state_modules = [
            demo_loader,
            eventhandler.PygameEventHandler(),
            director.Director()
        ]

        # Render modules.
        self.render_modules = [
            graphics.PygameGraphics(self.data),
            cleaner.Cleaner()
        ]

        # Initialize main loop.
        super().__init__(1.0 / self.data.config.fps, self.data.config.max_frame_time)

    def render(self, run_time, delta_time):
        for module in self.render_modules:
            module.tick(run_time, delta_time, self.data)

    def update(self, run_time, delta_time):
        for module in self.state_modules:
            module.tick(run_time, delta_time, self.data)

if __name__ == '__main__':
    app = MainLoopImp()
    app.start()