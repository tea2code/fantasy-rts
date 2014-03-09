import math

class Factory:
    """ A factory for points. Allows to use Point as a Flyweight pattern.

    Constant:
    FAST_EQ -- Indicates if the resulting Point should be with using fast
               equality allowing it to use the Flyweight pattern.

    Member:
    _points -- Maps already created points (dict).
    """

    FAST_EQ = True
    _points = {}

    @staticmethod
    def new_point(x=0, y=0, z=0):
        """ Create new point. """
        if Factory.FAST_EQ:
            key = (x, y, z)
            if key not in Factory._points:
                Factory._points[key] = Point(x, y, z, True)
            return Factory._points[key]
        else:
            return Point(x, y, z, False)

class Point:
    """ A int based immutable 3D point.

    Member:
    x -- The x component (float).
    y -- The y component (float).
    z -- The z component (float).
    _fast_eq -- Indicates if a fast equality check by id can be made (bool).
    _hash -- Cache for hash value (int).
    _length -- Cache for length value (float).
    _x -- The real x component (int).
    _y -- The real y component (int).
    _z -- The real z component (int).
    """

    __slots__ = ('_fast_eq', '_hash', '_length', '_x', '_y', '_z')

    def __init__(self, x=0, y=0, z=0, fast_eq=False):
        self._x = x
        self._y = y
        self._z = z
        self._hash = None
        self._fast_eq = fast_eq
        self._length = None

    @property
    def x(self):
        return self._x

    @property
    def y(self):
        return self._y

    @property
    def z(self):
        return self._z

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
        if self._length is None:
            self._length = math.sqrt((self._x * self._x) + (self._y * self._y) + (self._z * self._z))
        return self._length

    def tuple2(self):
        """ Returns a tuple representation of this point containing only x and y.

        Test:
        >>> v = Point(1, 2, 3)
        >>> v.tuple2()
        (1, 2)
        """
        return self._x, self._y

    def tuple3(self):
        """ Returns a tuple representation of this point.

        Test:
        >>> v = Point(1, 2, 3)
        >>> v.tuple3()
        (1, 2, 3)
        """
        return self._x, self._y, self._z

    def __add__(self, other):
        """ Add two points using + operator. Returns the resulting point.

        Test:
        >>> v1 = Point(1, 2, 1)
        >>> v2 = Point(3, 4, 1)
        >>> v3 = v1 + v2
        >>> v3.tuple3()
        (4, 6, 2)
        """
        x = self._x + other._x
        y = self._y + other._y
        z = self._z + other._z
        if self._fast_eq:
            return Factory.new_point(x, y, z)
        else:
            return Point(x, y, z)

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
        if self._fast_eq:
            return self
        else:
            return Point(self._x, self._y, self._z)

    def __eq__(self, other):
        """ Equality using the == operator.

        Test:
        >>> v1 = Point(1, 21, 1)
        >>> v2 = Point(1, 21, 1)
        >>> v3 = Point(1, 22, 1)
        >>> v1 == v2
        True
        >>> v1 == v3
        False
        >>> v1 = Point(1, 21, 1, True)
        >>> v2 = v1
        >>> v3 = Point(1, 22, 1, True)
        >>> v1 == v2
        True
        >>> v1 == v3
        False
        """
        if self._fast_eq and other._fast_eq:
            return id(self) == id(other)
        else:
            return self._x == other._x and  \
                   self._y == other._y and \
                   self._z == other._z

    def __hash__(self):
        """ Calculates hash of point.

        Test:
        >>> v1 = Point(1, 21, 1)
        >>> v2 = Point(1, 21, 1)
        >>> v3 = Point(1, 22, 1)
        >>> hash(v1) == hash(v2)
        True
        >>> hash(v1) == hash(v3)
        False
        """
        if self._hash is None:
            self._hash = hash(self.tuple3())
        return self._hash

    def __mul__(self, scalar):
        """ Scalar multiplication using the * operator. Returns the resulting point.

        Test:
        >>> v1 = Point(1, 2, 3)
        >>> v2 = v1 * 5
        >>> v2.tuple3()
        (5, 10, 15)
        """
        x = self._x * scalar
        y = self._y * scalar
        z = self._z * scalar
        if self._fast_eq:
            return Factory.new_point(x, y, z)
        else:
            return Point(x, y, z)

    def __str__(self):
        template = 'Point({}, {}, {})'
        return template.format(self._x, self._y, self._z)

    def __sub__(self, other):
        """ Subtract two points using - operator. Returns resulting point.

        Test:
        >>> v1 = Point(1, 4, 3)
        >>> v2 = Point(3, 2, 2)
        >>> v3 = v1 - v2
        >>> v3.tuple3()
        (-2, 2, 1)
        """
        x = self._x - other._x
        y = self._y - other._y
        z = self._z - other._z
        if self._fast_eq:
            return Factory.new_point(x, y, z)
        else:
            return Point(x, y, z)

if __name__ == '__main__':
    print('Executing doctest.')
    import doctest
    doctest.testmod()