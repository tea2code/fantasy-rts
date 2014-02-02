import config
import logging, logging.config
import yaml

from ai import director
from data import data
from demo import demo
from general import cleaner
from general import mainloop
from ui import eventhandler, graphics

class MainLoopImp(mainloop.MainLoop):
    """
    Constants:
    CONFIG_DIR -- Directory of the configuration (string).
    CONFIG_LOAD_FILE -- File with load order of config (string).

    Member:
    data -- The data module (data.Data).
    render_modules -- Modules regarding rendering the state (list).
    state_modules -- Modules regarding updating the state (list).
    """

    CONFIG_DIR = 'mod/'
    CONFIG_LOAD_FILE = 'mod.yaml'

    def __init__(self):
        # Data.
        self.data = data.Data()
        self.data.config.config_dir = self.CONFIG_DIR

        # Load configuration.
        config.load_config(self.data, self.CONFIG_DIR, self.CONFIG_LOAD_FILE)

        # Demo mode.
        demo_loader = demo.Demo(self.data)
        demo_loader.load()

        # State modules.
        self.state_modules = [
            demo_loader,
            eventhandler.PygameEventHandler(self.data),
            director.Director()
        ]

        # Render modules.
        self.render_modules = [
            graphics.PygameGraphics(self.data),
            cleaner.RenderCleaner()
        ]

        # Initialize main loop.
        super().__init__(1.0 / self.data.config.fps, self.data.config.max_frame_time)

    def render(self, run_time, delta_time, tick):
        for module in self.render_modules:
            module.tick(run_time, delta_time, self.data, tick)

    def update(self, run_time, delta_time, tick):
        for module in self.state_modules:
            module.tick(run_time, delta_time, self.data, tick)

if __name__ == '__main__':
    # Initialize logging.
    log_file = 'log/config.yaml'
    with open(log_file, 'r') as file:
        logging_config = yaml.safe_load(file)
    logging.config.dictConfig(logging_config)
    logger = logging.getLogger(__name__)
    logger.info('Starting game')

    # Start app.
    app = MainLoopImp()
    app.start()