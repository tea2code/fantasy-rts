class DynamicEntity():
    """ A dynamic entity config.

    Member:
    blocked -- List of blocked ids (list).
    """

    def __init__(self):
        self.blocked = []
        self.move_type = ''
        self.speed = 0.0