from . import tile

class Level(dict):
    """ Represents one map level. Implemented as a dict which is mapping
    the tile (value) at a certain position (key).

    Member:
    default_tile -- The default tile for a unknown position (data.tile).
    """

    def __init__(self,*arg,**kw):
        super().__init__(*arg, **kw)
        self.default_tile = tile.PLAIN