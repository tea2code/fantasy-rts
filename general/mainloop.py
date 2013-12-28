import time

from abc import ABCMeta, abstractmethod

class MainLoop(metaclass=ABCMeta):
    """ Abstract class implementing a main loop based on a semi-fixed timestep.
    See http://gafferongames.com/game-physics/fix-your-timestep/ for more
    information.

    Member:
    delta_time -- The time a frame should take (float).
    max_frame_time -- The maximum time an update may take before calling the
                      renderer.
    """

    def __init__(self, delta_time, max_frame_time):
        self.delta_time = delta_time
        self.max_frame_time = max_frame_time

    @abstractmethod
    def render(self, run_time, delta_time):
        """ Implement this function with any code related to rendering. """
        pass

    def start(self):
        """ Starts the main loop. """
        run_time = 0.0
        current_time = self.__high_res_time()
        accumulator = 0.0

        while True:
            new_time = self.__high_res_time()
            # Limit frame time to a maximum to avoid spiral of death.
            frame_time = min(new_time - current_time, self.max_frame_time)
            current_time = new_time

            accumulator += frame_time

            while accumulator >= self.delta_time:
                self.update(run_time, self.delta_time)
                accumulator -= self.delta_time
                run_time += self.delta_time

            self.render(run_time, self.delta_time)

    @abstractmethod
    def update(self, run_time, delta_time):
        """ Implement this function with any code related to updating the
        state.
        """
        pass

    def __high_res_time(self):
        """ Returns time in seconds in high resolution. """
        return time.perf_counter()