import math

from gamemath import comparison, gamemath

class Point:
    """ A float based 2D point which uses integer for comparison and hashing.

    Member:
    x -- The x component (float).
    y -- The y component (float).
    z -- The z component (float).
    _hash -- Cache for hash value (int).
    _x -- The real x component (float).
    _y -- The real y component (float).
    _z -- The real z component (float).
    _xi -- The rounded x component (int).
    _yi -- The rounded y component (int).
    _zi -- The rounded z component (int).
    """

    __slots__ = ('_hash', '_x', '_y', '_z', '_xi', '_yi', '_zi')

    def __init__(self, x=0.0, y=0.0, z=0.0):
        self.x = x
        self.y = y
        self.z = z

    @property
    def x(self):
        return self._x

    @property
    def int_x(self):
        return self._xi

    @x.setter
    def x(self, value):
        self._x = value
        self._xi = gamemath.int_round(value)
        self._hash = None

    @property
    def y(self):
        return self._y

    @property
    def int_y(self):
        return self._yi

    @y.setter
    def y(self, value):
        self._y = value
        self._yi = gamemath.int_round(value)
        self._hash = None

    @property
    def z(self):
        return self._z

    @property
    def int_z(self):
        return self._zi

    @z.setter
    def z(self, value):
        self._z = value
        self._zi = gamemath.int_round(value)
        self._hash = None

    def clone(self):
        """ Creates a copy of this point with same x and y.

        Test:
        >>> v = Point(1, 2, 3)
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
        >>> v1 = Point(1.0001, 21.0001, 1.0001)
        >>> v2 = Point(1.0001, 21.0001, 1.0001)
        >>> v3 = Point(1.0001, 21.000100001, 1.0001)
        >>> v1.exact_eq(v2)
        True
        >>> v1.exact_eq(v3)
        False
        """
        return comparison.float_equal(self._x, other._x) and \
               comparison.float_equal(self._y, other._y) and \
               comparison.float_equal(self._z, other._z)

    def length(self):
        """ Calculates the length of a point.

        Test:
        >>> print('{0:.3f}'.format(Point(1, 1, 1).length()))
        1.732
        >>> print('{0:.3f}'.format(Point(45, 127, 10).length()))
        135.107
        >>> print('{0:.3f}'.format(Point(5, 3, 2).length()))
        6.164
        >>> print('{0:.3f}'.format(Point(-1, 1, 1).length()))
        1.732
        >>> print('{0:.3f}'.format(Point(45, -127, -10).length()))
        135.107
        >>> print('{0:.3f}'.format(Point(-5, -3, -2).length()))
        6.164
        >>> print('{0:.3f}'.format(Point(1, 2, 3).length()))
        3.742
        """
        return math.sqrt((self._x * self._x) + (self._y * self._y) + (self._z * self._z))

    def tuple2(self):
        """ Returns a tuple representation of this point containing only x and y.

        Test:
        >>> v = Point(1.1, 2.5, 3.0)
        >>> v.tuple2()
        (1.1, 2.5)
        """
        return self._x, self._y

    def tuple3(self):
        """ Returns a tuple representation of this point.

        Test:
        >>> v = Point(1.1, 2.5, 3.0)
        >>> v.tuple3()
        (1.1, 2.5, 3.0)
        """
        return self._x, self._y, self._z

    def int_tuple2(self):
        """ Returns a tuple representation of this point containing only x and
        y rounded to next integer.

        Test:
        >>> v = Point(1.1, 2.5, 3.0)
        >>> v.int_tuple2()
        (1, 3)
        """
        return self._xi, self._yi

    def int_tuple3(self):
        """ Returns a tuple representation of this point rounded to next integer.

        Test:
        >>> v = Point(1.1, 2.5, 3.0)
        >>> v.int_tuple3()
        (1, 3, 3)
        """
        return self._xi, self._yi, self._zi

    def __add__(self, other):
        """ Add two points using + operator. Returns the resulting point.

        Test:
        >>> v1 = Point(1, 2, 1)
        >>> v2 = Point(3, 4, 1)
        >>> v3 = v1 + v2
        >>> v3.x
        4
        >>> v3.y
        6
        >>> v3.z
        2
        """
        return Point(self._x + other._x, self._y + other._y, self._z + other._z)

    def __copy__(self):
        """ Used when copy.copy() is called on a point.

        Test:
        >>> import copy
        >>> v = Point(1, 2, 3)
        >>> c = copy.copy(v)
        >>> v is c
        False
        >>> v == c
        True
        """
        return Point(self._x, self._y, self._z)

    def __eq__(self, other):
        """ Equality using the == operator.

        Test:
        >>> v1 = Point(1.0001, 21.45, 1.0001)
        >>> v2 = Point(1.0001, 21.45, 1.0001)
        >>> v3 = Point(1.0001, 21.5, 1.0001)
        >>> v1 == v2
        True
        >>> v1 == v3
        False
        """
        return self._xi == other._xi and  \
               self._yi == other._yi and \
               self._zi == other._zi

    def __hash__(self):
        """ Calculates hash of point.

        Test:
        >>> v1 = Point(1.0001, 21.45, 1.0001)
        >>> v2 = Point(1.0001, 21.45, 1.0001)
        >>> v3 = Point(1.0001, 21.5, 1.0001)
        >>> hash(v1) == hash(v2)
        True
        >>> hash(v1) == hash(v3)
        False
        >>> v3.y = 21.45
        >>> hash(v1) == hash(v3)
        True
        """
        if self._hash is None:
            self._hash = hash(self.int_tuple3())
        return self._hash

    def __mul__(self, scalar):
        """ Scalar multiplication using the * operator. Returns the resulting point.

        Test:
        >>> v1 = Point(1, 2, 3)
        >>> v2 = v1 * 5
        >>> v2.x
        5
        >>> v2.y
        10
        >>> v2.z
        15
        """
        return Point(self._x * scalar, self._y * scalar, self._z * scalar)

    def __str__(self):
        template = 'Point({:.2f}, {:.2f}, {:.2f})'
        return template.format(self._x, self._y, self._z)

    def __sub__(self, other):
        """ Subtract two points using - operator. Returns resulting point.

        Test:
        >>> v1 = Point(1, 4, 3)
        >>> v2 = Point(3, 2, 2)
        >>> v3 = v1 - v2
        >>> v3.x
        -2
        >>> v3.y
        2
        >>> v3.z
        1
        """
        return Point(self._x - other._x, self._y - other._y, self._z - other._z)

if __name__ == '__main__':
    print('Executing doctest.')
    import doctest
    doctest.testmod()