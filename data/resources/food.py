class Food:
    """ Represents a food resources.

    Member:
    nutrition -- The nutritional value of this food (float).
    """

    def __init__(self, nutrition):
        self.nutrition = nutrition

    def __str__(self):
        return 'Food({0:.2f})'.format(self.nutrition)