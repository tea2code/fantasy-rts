class Input:
    """ The input state.

    Member:
    keys_pressed -- List of currently pressed keys (list).
    mouse_pressed -- Indicates that the mouse button is currently pressed (bool).
    next_key_execution -- Indicates timestamp of next execution of pressed keys (float).
    """

    def __init__(self):
        self.keys_pressed = []
        self.mouse_pressed = False
        self.next_key_execution = 0.0