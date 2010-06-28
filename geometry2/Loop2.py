from __future__ import print_function

from Shape2 import Shape2
from Vertex2 import Vertex2

class Loop2(Shape2):
    """a loop defined by a series of vertices
       
       used to synthesize polylines from line segment data
    """
    EPSILON = 0.1
    SPECIES = {"interior" : 0, "exterior" : 1}
    
    def __init__(self, vertices=None, idstring="noname"):
        Shape2.__init__(self) # inits the following:
        #self._vertices = []
        #self._bounds = None
        
        self.idstring = idstring
        self.closed = False
        self.species = None
        self.polygon = None
    
        if vertices is not None:
            self._vertices = list(vertices)
            self.closed = True

    def __repr__(self):
        return "<loop {0}>".format(self.idstring)
    
    def __cmp__(self, other):
        """sort loops by minimum vertex
        """
        return cmp(min(self._vertices), min(other._vertices))
        
    def add_pair(self, a, b):
        self._bounds = None # invalidate bounds when data changes
        
        if self.closed:
            return False
        
        if len(self._vertices) == 0:
            self._vertices.append(a)
            self._vertices.append(b)
            return True
        
        # test forward and back
        for y, z in ((a, b), (b, a)):
            if self._vertices[0] == y:
                if self._vertices[-1] == z:
                    self.closed = True
                    return True
                
                if len(self._vertices) > 1 and self._vertices[1] == z:
                    raise ValueError("duplicate pair!")
                
                self._vertices.insert(0, z)
                return True
            
            if self._vertices[-1] == y:
                if self._vertices[0] == z:
                    self.closed = True
                    return True
                
                if len(self._vertices) > 1 and self._vertices[-2] == z:
                    raise ValueError("duplicate pair!")
                
                self._vertices.append(z)
                return True
        
        # if neither vertex on neither end of loop return false
        return False
    
    def find_ear(self):
        """return 3 vertices that form an ear
        """
        if len(self._vertices) < 3:
            raise ValueError("no ear in loop with fewer than 3 vertices!")
        if not self.closed:
            raise ValueError("won't find ear for open loop!")
        
        # init ear search
        vs = iter(self)
        a = None
        b = vs.next()
        c = vs.next()
        
        # loop over vertices looking for ear
        for v in vs:
            a = b
            b = c
            c = v
            if self._test_ear(a, b, c):
                return (a, b, c)

        raise ValueError("wtf? failed to find ear!")
    
    def _test_ear(self, a, b, c):
        """test potential ear
        """
        #print("testing", a, b, c, "for ear")
        
        # test if midpoint of ac is inside loop
        mid_ac = a + ((c - a) * 0.5)
        
        #print("\tmidpoint of ac:", mid_ac)
        
        if not self.contains(mid_ac):
            #print("\tfail: midpoint not contained!")
            return False
        
        # build triangle loop to test points
        ear = Loop2([a, b, c])
        
        # check winding of vertices except these 3
        for v in (x for x in self if x not in (a, b, c)):
            if ear.contains(v):
                #print("\tfail:", v, "contained by ear", a, b, c)
                return False
        
        #print("\tftw!", a, b, c, "is an ear")
        return True
        
    def winding(self, vertex):
        """return the angular winding from vertex to the points of this loop
        """
        if not self.closed:
            raise ValueError("no winding for open loop!")
        
        # set up winding iteration
        degrees = 0.0
        vertices = list(self)
        a = None
        b = vertices.pop(0) # seed with first vertex
        vertices.append(b) # add first vertex back to end to close loop
        
        # sum winding around loop
        for v in vertices:
            a = b
            b = v
            step = (a - vertex).angle_to(b - vertex)
            if step > 180.0:
                step = step - 360.0
            degrees += step
                
        #print("winding: {0:.2f}".format(degrees))
        
        return degrees
    
    def contains(self, vertex):
        """test whether this loop contains given vertex
        """
        if not self.bounds.contains(vertex):
            return False
        if abs(self.winding(vertex) - 360.0) < self.EPSILON:
            return True
        return False
    
    def surrounds(self, loop):
        """tests whether given loop falls completely inside of this loop
        """
        if not self.bounds.touches(loop.bounds):
            return False
        
        for vertex in loop:
            if not self.contains(vertex):
                return False
        
        return True
        
    def is_forward(self):
        """returns true if loop has counterclockwise winding
           
           (ccw winding is opengl default for forward-facing face)
        """
        # find lowest point
        vs = iter(self)
        first = vs.next()
        for v in vs:
            if v.y < first.y:
                first = v
            elif v.y == first.y and v.x < first.x:
                first = v
                
        # find vertex with lowest heading from first point
        next = None
        hmin = 360.0
        for v in (x for x in self if x != first):
            vh = (v - first).heading
            if vh < hmin:
                hmin = vh
                next = v
        
        # find vertex with lowest angle from (next - current)
        nc = next - first
        last = None
        dmin = 360.0
        for v in (x for x in self if x not in (next, first)):
            vd = nc.angle_to(v - next)
            if vd < dmin:
                dmin = vd
                last = v
        
        # start at index of first and see whether we come to next or last first
        i = self._vertices.index(first)
        while True:
            i += 1
            if i == len(self._vertices):
                i = 0
            if self._vertices[i] == next:
                return True
            if self._vertices[i] == last:
                return False
            
            
        
        
