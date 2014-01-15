from data.task import Factory

class Director:
    """ The AI director manages all behaviour. """

    def tick(self, run_time, delta_time, data):
        # Execute tasks.
        for task in data.game.tasks.take(run_time):
            more_steps = task.execute_next(data)
            if more_steps:
                data.game.tasks.insert(task.time(), task)
            else:
                self.__new_task(task.entity, run_time, data)
        print()

    def __new_task(self, entity, run_time, data):
        """ Get the next task for the given entity. """
        Factory.new_add_idle_task(entity, run_time, data)