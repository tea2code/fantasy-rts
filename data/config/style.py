class Style:
    """ A style config.

    Member:
    default_mapping -- The default sprite id to use (string).
    images -- Image id to path mapping (dict).
    mappings -- Entity id to sprite id mapping (dict).
    sprites -- Sprite id to sprite mapping (dict).
    """

    def __init__(self):
        self.default_mapping = ''
        self.images = {}
        self.mappings = {}
        self.sprites = {}