from __future__ import print_function

from Shape2 import Shape2

class Facet2(Shape2):
    """a triangle composed of 3 vertices and 3 edges
    """
    
    def __init__(self, ea, eb, ec):
        Shape2.__init__(self) # inits the following:
        #self._vertices = []
        #self._bounds = None
        
        self.polygon = None # polygon this facet belongs to
                
        # set smallest edge to be first
        self._edges = [ea, eb, ec]
        em = min(self._edges)
        i = self._edges.index(em)
        self._edges = self._edges[i:] + self._edges[:i]
        
        # set vertices
        for edge in self._edges:
            self._vertices.append(edge.a)
        
    def __cmp__(self, other):
        ca = cmp(self.a, other.a)
        if ca != 0:
            return ca
        cb = cmp(self.b, other.b)
        if cb != 0:
            return cb
        cc = cmp(self.c, other.c)
        if cc != 0:
            raise ValueError("facets {0} and {1} overlap!".format(self, other))
        return 0
    
    def __repr__(self):
        return "<f {0} {1} {2}>".format(*self)
    
    @property
    def a(self):
        return self._vertices[0]
    
    @property
    def b(self):
        return self._vertices[1]
        
    @property
    def c(self):
        return self._vertices[2]

