class Edge2:
    """an edge between two vertices
    """
    
    SPECIES = set(["inside", "outside", "fill"])
    
    def __init__(self, a, b):
        self.vertices = [a, b] # should follow the right hand rule
        self.facet = None
        self.species = None
        
    def __repr__(self):
        return "<e {0} {1}>".format(*self.vertices)
        
    def __cmp__(self, other):
        ca = cmp(self.a, other.a)
        if ca != 0:
            return ca
        return cmp(self.b, other.b)
    
    @property
    def a(self):
        return self.vertices[0]
    
    @property
    def b(self):
        return self.vertices[1]
    

        
