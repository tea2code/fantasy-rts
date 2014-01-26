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
    image -- The image id (string).
    x -- The x coordinate (int).
    y -- The y coordinate (int).
    chance -- The chance that this image appears. Only necessary for multiples (float).
    """

    def __init__(self, image, x, y):
        self.image = image
        self.x = x
        self.y = y
        self.chance = 1.0

class Style:
    """ A style config.

    Member:
    default_mapping -- The default sprite id to use (string).
    images -- Image id to image mapping (dict).
    mappings -- Object id to sprite id mapping (dict).
    sprites -- Sprite id to sprite or list of sprites mapping (dict).
    """

    def __init__(self):
        self.default_mapping = ''
        self.images = {}
        self.mappings = {}
        self.sprites = {}