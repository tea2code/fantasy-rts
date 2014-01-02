from data import point

class Shrub:
    """ A shrub which may contain food.

    Member:
    food -- The food resource (data.resource.food).
    pos -- The position of the shrub (data.point).
    """

    def __init__(self, food=None):
        self.food = food
        self.pos = point.Point()