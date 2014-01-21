class Image:
    """ A image config.

    Member:
    path -- The image path (string).
    """

    def __init__(self):
        self.path = ''

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

class Style:
    """ A style config.

    Member:
    default_mapping -- The default sprite id to use (string).
    images -- Image id to image mapping (dict).
    mappings -- Object id to sprite id mapping (dict).
    sprites -- Sprite id to sprite mapping (dict).
    """

    def __init__(self):
        self.default_mapping = ''
        self.images = {}
        self.mappings = {}
        self.sprites = {}