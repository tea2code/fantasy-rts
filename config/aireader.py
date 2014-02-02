from . import basereader
from data.config import ai

class YamlAiReader(basereader.BaseYamlReader):
    """ Yaml reader for ai types.

    Constants:
    NAME
    NAMESPACE
    PARAMETERS
    TASK
    TYPE
    VALUE
    VARIANCE_MIN
    VARIANCE_MAX
    """

    NAME = 'name'
    NAMESPACE = 'namespace'
    PARAMETERS = 'parameters'
    TASK = 'task'
    TASKS = 'tasks'
    TYPE = 'type'
    VALUE = 'value'
    VARIANCE_MIN = 'variance_min'
    VARIANCE_MAX = 'variance_max'

    def parse(self, root, data):
        """ Parse the task structure. Writes the parsed information into the
        data object. """

        namespace = self.read_req_string(root, self.NAMESPACE)

        if self.has(root, self.TASKS):
            self.__tasks(namespace, root, data)

    def __tasks(self, namespace, root, data):
        """ Task config. """
        tasks = self.read_req_object(root, self.TASKS)
        namespace_list = [namespace, self.read_req_string(tasks, self.NAMESPACE)]

        default_variance_min = self.read_float(tasks, self.VARIANCE_MIN, 0.0)
        default_variance_max = self.read_float(tasks, self.VARIANCE_MAX, 0.0)

        for task in self.read_object(tasks, self.TASK, []):
            name = self.read_req_string(task, self.NAME)
            id = self.namespace_to_id(namespace_list, name)
            type = self.read_req_string(task, self.TYPE)
            task_obj = ai.Task(type)
            task_obj.variance_min = self.read_float(task, self.VARIANCE_MIN, default_variance_min)
            task_obj.variance_max = self.read_float(task, self.VARIANCE_MAX, default_variance_max)

            for param in self.read_object(task, self.PARAMETERS, []):
                param_type = self.read_req_string(param, self.TYPE)
                param_value = self.read_req_object(param, self.VALUE)
                task_obj.parameters[param_type] = param_value

            data.config.tasks[id] = task_obj