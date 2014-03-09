class Key:
    """ A key configuration.

    Member:
    key -- The key (string).
    modifier -- The key modifier (string).
    """

    def __init__(self, key, modifier=None):
        self.key = key
        self.modifier = modifier
