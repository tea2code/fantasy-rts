import logging
import logging.config

import yaml

import config
from ai import director
from data import data
from demo import demo
from general import cleaner
from general import decisiontreerenderer as dtr
from general import mainloop
from ui import eventhandler, graphics


class MainLoopImp(mainloop.MainLoop):
    """
    Constants:
    CONFIG_DIR -- Directory of the configuration (string).
    CONFIG_LOAD_FILE -- File with load order of config (string).
    LOG_DIR -- Directory for logging (string).
    LOG_CONFIG_FILE -- The log config file (string).
    DECISION_GRAPH_DIR -- The decision graph directory (string).
    DECISION_GRAPH_FILE -- Template for decision graph files (string).

    Member:
    data -- The data module (data.Data).
    logger -- The logger (logging).
    render_modules -- Modules regarding rendering the state (list).
    state_modules -- Modules regarding updating the state (list).
    """

    CONFIG_DIR = 'mod/'
    CONFIG_LOAD_FILE = 'mod.yaml'
    LOG_DIR = 'log/'
    LOG_CONFIG_FILE = LOG_DIR + 'config.yaml'
    LOG_TEXT_EXCEPTION = 'Exception thrown'
    DECISION_GRAPH_DIR = LOG_DIR + 'decision/'
    DECISION_GRAPH_FILE = '{0}.{1}'

    def __init__(self):
        # Logging.
        self.__setup_log()
        self.logger.info('Starting game')

        try:
            # Data.
            self.data = data.Data()
            self.data.config.config_dir = self.CONFIG_DIR

            # Load configuration.
            config.load_config(self.data, self.CONFIG_DIR, self.CONFIG_LOAD_FILE)

            # Draw decision trees.
            if self.data.config.render_decision_trees:
                renderer = dtr.DecisionTreeRenderer(self.DECISION_GRAPH_DIR, self.DECISION_GRAPH_FILE)
                renderer.render(self.data.game.decision_tree.start_nodes, self.data.game.decision_tree.nodes)

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
        except:
            self.logger.exception(self.LOG_TEXT_EXCEPTION)
            raise

    def render(self, run_time, delta_time, tick):
        try:
            for module in self.render_modules:
                module.tick(run_time, delta_time, self.data, tick)
        except SystemExit:
            # Everything is ok. Just normal application exit.
            raise
        except:
            self.logger.exception(self.LOG_TEXT_EXCEPTION)
            raise

    def update(self, run_time, delta_time, tick):
        try:
            for module in self.state_modules:
                module.tick(run_time, delta_time, self.data, tick)
        except SystemExit:
            # Everything is ok. Just normal application exit.
            raise
        except:
            self.logger.exception(self.LOG_TEXT_EXCEPTION)
            raise

    def __setup_log(self):
        """ Setup logging. """
        with open(self.LOG_CONFIG_FILE, 'r') as file:
            logging_config = yaml.safe_load(file)
        logging.config.dictConfig(logging_config)
        self.logger = logging.getLogger(__name__)

if __name__ == '__main__':
    app = MainLoopImp()
    app.start()