class Sprite:
    """ A config sprite.

    Member:
    height -- The height (int).
    image -- The image id (string).
    width -- The width (int).
    x -- The x coordinate (int).
    y -- The y coordinate (int).
    """

    def __init__(self, image, x, y, width, height):
        self.image = image
        self.x = x
        self.y = y
        self.width = width
        self.height = height