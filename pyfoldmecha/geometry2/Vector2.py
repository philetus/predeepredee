import numpy
from math import sin, cos, acos, atan2, degrees, radians

class Vector2:
    """2d vector using numpy library to implement storage and methods

       coords stored as a numpy array named 'coords'
    """
    # instances only store coords array
    __slots__ = "_coords"
    EPSILON = 0.01

    def __init__(self, x, y):
        #store x and y coordinates in numpy array
        self._coords = numpy.array( [float(c) for c in (x, y)], 'd' )

    def __iter__(self):
        for coord in self._coords:
            yield coord

    def __repr__(self):
        return "<v {0:.3f} {1:.3f}>".format(*self)

    @property
    def x(self):
        return self._coords[0]    
    @x.setter
    def x(self, value):
        self._coords[0] = value

    @property
    def y(self):
        return self._coords[1]
    @y.setter
    def y(self, value):
        self._coords[1] = value

    @property
    def magnitude(self):
        """length of vector
        """
        return numpy.sqrt(sum(c**2 for c in self))

    def add(self, vector):
        """add given vector to this vector and return as new vector
        """
        return self.__class__(*(c.item() for c in
                                numpy.add(self._coords, vector._coords)[:3]))

    def __add__(self, vector):
        """a + b <==> a.add( b )
        """
        return self.add(vector)

    def subtract(self, vector):
        """subtract given vector from this vector and return as new vector
        """
        return self.__class__(*(c.item() for c in
                                numpy.subtract(self._coords,
                                               vector._coords)[:3]))

    def __sub__(self, vector):
        """a - b <==> a.subtract( b )
        """
        return self.subtract(vector)

    def dot(self, vector):
        """returns scalar dot product of this vector and given vector
        """
        return numpy.dot(self._coords[:3].transpose(),
                         vector._coords[:3]).item()

    def cross(self, vector):
        """cross this vector with given vector and return as new vector
        """
        return self.__class__(*numpy.cross(self._coords.A1[:3],
                                           vector._coords.A1[:3]))

    def multiply(self, scalar):
        """multiply this vector by given scalar and return as new vector
        """
        return self.__class__(*(c.item() for c in
                                numpy.multiply(self._coords,
                                               float(scalar))[:3]))

    def __mul__(self, scalar):
        """v * s <==> v.multiply(s)
        """
        return self.multiply(scalar)

    def divide(self, scalar):
        """divide this vector by given scalar and return as new vector
        """
        # check we aren't dividing by 0
        if scalar == 0.0:
            raise ZeroDivisionError("attempted to divide vector by 0!")
        return self.__class__(*(c.item() for c in
                                numpy.divide(self._coords,
                                             float(scalar))[:3]))
    
    def normalize(self):
        """return new vector with same heading and magnitude of 1.0
        """
        # assure magnitude > 0
        magnitude = self.magnitude
        if magnitude == 0.0:
            raise ZeroDivisionError("can't normalize vector of magnitude 0!")
        return self.divide(magnitude)

    def project(self, vector):
        """project this vector onto given vector and return as new vector
        """
        return vector.multiply(self.dot(vector) / (vector.magnitude**2))
  
    def angle_to(self, vector):
        """positive angle in degrees from this vector to given vector
           
           counterclockwise is positive (opengl default)
        """
        angle = vector.heading - self.heading
        if angle < 0:
            angle += 360
        return angle
            
    @property
    def heading(self):
        """return heading in degrees for vector
        """
        if self.magnitude < self.EPSILON:
            raise ValueError("no heading for zero magnitude vector!")
            
        heading = degrees(atan2(self.y, self.x))
        if heading < 0.0:
            heading = 360.0 + heading
        
        return heading
        
    def a_angle_to( self, vector ):
        """return angle from this vector to given vector in degrees
        """
        try:
            return degrees( acos(self.normalize().dot(vector.normalize())) )
        except ValueError:
            if self._get_magnitude() > 0 and vector._get_magnitude() > 0:
                return 0.0
            raise ValueError( "couldn't calculate angle from %s to %s!"
                              % (self, vector) )

    def cross(self):
        """rotate vector by 90 degrees
        """
        return self.__class__(-self._coords[1], self._coords[0])
        
    def rotate(self, degrees):
        """rotate this vector by given degrees and return as new vector
        """
        # cosine vector is this vector multiplied by cosine of angle
        cosine = self.multiply(cos(radians(degrees)))

        # sine vector is cross product of this vector and normalized given
        # vector, multiplied by sine of angle
        sine = self.cross().multiply(sin(radians(degrees)))

        return cosine.add(sine)

