from general import mainloop
from ui import eventhandler, graphics

class MainLoopImp(mainloop.MainLoop):
    """
    Constants:
    FPS -- Frames per second (int).
    MAX_FRAME_TIME -- Maximum time a frame may take (float).

    Member:
    event_handler -- The event handler.
    graphics -- The graphic renderer.
    """
    FPS = 100
    MAX_FRAME_TIME = 0.25

    def __init__(self):
        super().__init__(1.0 / self.FPS, self.MAX_FRAME_TIME)

        self.event_handler = eventhandler.PygameEventHandler()
        self.graphics = graphics.PygameGraphics()

    def render(self, run_time, delta_time):
        self.graphics.tick(run_time, delta_time)

    def update(self, run_time, delta_time):
        self.event_handler.tick(run_time, delta_time)

if __name__ == '__main__':
    app = MainLoopImp()
    app.start()