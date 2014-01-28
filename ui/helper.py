""" Some ui related helper functions. """

def is_visible(pos, graphics):
    """ Checks if a position is visible on screen.

    Test:
    >>> from data.world import point
    >>> from data import graphics
    >>> g = graphics.Graphics()
    >>> g.view_offset_x = 1
    >>> g.view_offset_y = 2
    >>> g.view_x = 5
    >>> g.view_y = 10
    >>> p = point.Point(0, 0)
    >>> is_visible(p, g)
    False
    >>> p = point.Point(1, 1)
    >>> is_visible(p, g)
    False
    >>> p = point.Point(1, 2)
    >>> is_visible(p, g)
    True
    >>> p = point.Point(3, 7)
    >>> is_visible(p, g)
    True
    >>> p = point.Point(6, 7)
    >>> is_visible(p, g)
    False
    >>> p = point.Point(3, 12)
    >>> is_visible(p, g)
    False
    """
    return graphics.view_offset_x <= pos.x < graphics.view_offset_x + graphics.view_x and \
           graphics.view_offset_y <= pos.y < graphics.view_offset_y + graphics.view_y

def pos_to_screen(pos, tile_x, tile_y):
    """ Convert world coordinates to tile position on screen. This
    returns the left upper corner.

    Test:
    >>> from data.world import point
    >>> p = point.Point(0, 0)
    >>> pos_to_screen(p, 16, 18)
    (0, 0)
    >>> p = point.Point(1, 2)
    >>> pos_to_screen(p, 16, 18)
    (16, 36)
    """
    return pos.x * tile_x, pos.y * tile_y

if __name__ == '__main__':
    print('Executing doctest.')
    import doctest
    doctest.testmod()