from gamemath import comparison, gamemath, pythagorean

class Point:
    """ A float based 2D point which uses integer for comparison and hashing.

    Member:
    x -- The x component (float).
    y -- The y component (float).
    _hash -- Cache for hash value (int).
    _x -- The real x component (float).
    _y -- The real y component (float).
    _xi -- The rounded x component (int).
    _yi -- The rounded y component (int).
    """

    __slots__ = ('_hash', '_x', '_y', '_xi', '_yi')

    def __init__(self, x=0.0, y=0.0):
        self.x = x
        self.y = y

    @property
    def x(self):
        return self._x

    @x.setter
    def x(self, value):
        self._x = value
        self._xi = gamemath.int_round(value)
        self._hash = None

    @property
    def y(self):
        return self._y

    @y.setter
    def y(self, value):
        self._y = value
        self._yi = gamemath.int_round(value)
        self._hash = None

    def clone(self):
        """ Creates a copy of this point with same x and y.

        Test:
        >>> v = Point(1, 2)
        >>> c = v.clone()
        >>> v is c
        False
        >>> v == c
        True
        """
        return self.__copy__()

    def exact_eq(self, other):
        """ Does an exact value comparison.

        Test:
        >>> v1 = Point(1.0001, 21.0001)
        >>> v2 = Point(1.0001, 21.0001)
        >>> v3 = Point(1.0001, 21.000100001)
        >>> v1.exact_eq(v2)
        True
        >>> v1.exact_eq(v3)
        False
        """
        return comparison.float_equal(self._x, other._x) and \
               comparison.float_equal(self._y, other._y)

    def length(self):
        """ Calculates the length of a point.

        Test:
        >>> print('{0:.3f}'.format(Point(1, 1).length()))
        1.414
        >>> print('{0:.3f}'.format(Point(45, 127).length()))
        134.737
        >>> print('{0:.3f}'.format(Point(5, 3).length()))
        5.831
        >>> print('{0:.3f}'.format(Point(-1, 1).length()))
        1.414
        >>> print('{0:.3f}'.format(Point(45, -127).length()))
        134.737
        >>> print('{0:.3f}'.format(Point(-5, -3).length()))
        5.831
        """
        return pythagorean.solve_c(self._x, self._y)

    def tuple(self):
        """ Returns a tuple representation of this point.

        Test:
        >>> v = Point(1.1, 2.5)
        >>> v.tuple()
        (1.1, 2.5)
        """
        return self._x, self._y

    def int_tuple(self):
        """ Returns a tuple representation of this point rounded to next integer.

        Test:
        >>> v = Point(1.1, 2.5)
        >>> v.int_tuple()
        (1, 3)
        """
        return self._xi, self._yi

    def __add__(self, other):
        """ Add two points using + operator. Returns the resulting point.

        Test:
        >>> v1 = Point(1, 2)
        >>> v2 = Point(3, 4)
        >>> v3 = v1 + v2
        >>> v3.x
        4
        >>> v3.y
        6
        """
        return Point(self._x + other._x, self._y + other._y)

    def __copy__(self):
        """ Used when copy.copy() is called on a point.

        Test:
        >>> import copy
        >>> v = Point(1, 2)
        >>> c = copy.copy(v)
        >>> v is c
        False
        >>> v == c
        True
        """
        return Point(self._x, self._y)

    def __eq__(self, other):
        """ Equality using the == operator.

        Test:
        >>> v1 = Point(1.0001, 21.45)
        >>> v2 = Point(1.0001, 21.45)
        >>> v3 = Point(1.0001, 21.5)
        >>> v1 == v2
        True
        >>> v1 == v3
        False
        """
        return self._xi == other._xi and self._yi == other._yi

    def __hash__(self):
        """ Calculates hash of point.

        Test:
        >>> v1 = Point(1.0001, 21.45)
        >>> v2 = Point(1.0001, 21.45)
        >>> v3 = Point(1.0001, 21.5)
        >>> hash(v1) == hash(v2)
        True
        >>> hash(v1) == hash(v3)
        False
        >>> v3.y = 21.45
        >>> hash(v1) == hash(v3)
        True
        """
        if self._hash is None:
            self._hash = hash(self.int_tuple())
        return self._hash

    def __mul__(self, scalar):
        """ Scalar multiplication using the * operator. Returns the resulting point.

        Test:
        >>> v1 = Point(1, 2)
        >>> v2 = v1 * 5
        >>> v2.x
        5
        >>> v2.y
        10
        """
        return Point(self._x * scalar, self._y * scalar)

    def __str__(self):
        return 'Point({:.2f}, {:.2f})'.format(self._x, self._y)

    def __sub__(self, other):
        """ Subtract two points using - operator. Returns resulting point.

        Test:
        >>> v1 = Point(1, 4)
        >>> v2 = Point(3, 2)
        >>> v3 = v1 - v2
        >>> v3.x
        -2
        >>> v3.y
        2
        """
        return Point(self._x - other._x, self._y - other._y)