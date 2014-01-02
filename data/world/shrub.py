from data import point

class Shrub:
    """ A shrub which may contain food.

    Member:
    food -- The food resources (data.resources.food).
    pos -- The position of the shrub (data.point).
    """

    def __init__(self, food=None):
        self.food = food
        self.pos = point.Point()

    def __str__(self):
        template = 'Shrub({0}, {1})'
        return template.format(self.pos, self.food)