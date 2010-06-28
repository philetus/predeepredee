from __future__ import print_function

from Shape2 import Shape2

class Edge2(Shape2):
    """an edge between two vertices
    """
    
    SPECIES = set(["inside", "outside", "fill"])
    
    def __init__(self, a, b):
        Shape2.__init__(self) # inits the following:
        #self._vertices = []
        #self._bounds = None

        self._vertices = [a, b] # should wind ccw
        self.facet = None
        self.loop = None
        self.species = None
        
    def __repr__(self):
        return "<e {0} {1}>".format(*self._vertices)
        
    def __cmp__(self, other):
        ca = cmp(self.a, other.a)
        if ca != 0:
            return ca
        return cmp(self.b, other.b)
    
    @property
    def a(self):
        return self._vertices[0]
    
    @property
    def b(self):
        return self._vertices[1]
    

        
